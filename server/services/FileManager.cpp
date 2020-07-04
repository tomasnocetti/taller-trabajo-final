#include "FileManager.h"
#include "../GameConfig.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>

// User defined class template specialization
namespace msgpack {
  MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS) {
  namespace adaptor {
    template<>
    struct convert<FileIndex> {
      msgpack::object const& operator()(
        msgpack::object const& o, FileIndex& v) const {
        FileIndex a = {
          o.via.array.ptr[0].as<std::size_t>()
        };
        memcpy(
          a.nick,
          o.via.array.ptr[1].as<std::string>().c_str(), STR_LEN);
        memcpy(
          a.password,
          o.via.array.ptr[2].as<std::string>().c_str(), STR_LEN);

        v = a;
        return o;
      }
    };

    template<>
    struct pack<FileIndex> {
      template <typename Stream>
      packer<Stream>& operator()(
        msgpack::packer<Stream>& o, FileIndex const& v) const {
        o.pack_array(3);
        o.pack_fix_uint32(v.playerId);
        o.pack_str(STR_LEN);
        o.pack_str_body(v.nick, STR_LEN);
        o.pack_str(STR_LEN);
        o.pack_str_body(v.password, STR_LEN);
        return o;
      }
    };


    template<>
    struct convert<PlayerPersistData> {
      msgpack::object const& operator()(
        msgpack::object const& o, PlayerPersistData& v) const {
        PlayerPersistData a = {
          o.via.array.ptr[0].as<std::size_t>(),
          o.via.array.ptr[1].as<std::size_t>(),
          o.via.array.ptr[2].as<std::size_t>(),
          o.via.array.ptr[3].as<std::size_t>(),
          o.via.array.ptr[4].as<std::size_t>(),
          o.via.array.ptr[5].as<std::size_t>(),
          o.via.array.ptr[6].as<std::size_t>(),
          o.via.array.ptr[7].as<PlayerRootData>(),
          o.via.array.ptr[8].as<int>(),
          o.via.array.ptr[9].as<int>(),
          {},
          {}
        };
        for (int i = 0; i < INVENTORY_SIZE; i++) {
          InventoryElementData inv =
            o.via.array.ptr[10 + i].as<InventoryElementData>();
          if (inv.itemId == 0) continue;
          a.inventory.push_back(inv);
        }
        for (int i = 0; i < INVENTORY_SIZE; i++) {
          InventoryElementData inv = o.via.array.ptr[
            10 + INVENTORY_SIZE + i].as<InventoryElementData>();
          if (inv.itemId == 0) continue;
          a.savedInventory.push_back(inv);
        }
        v = a;
        return o;
      }
    };

    template<>
    struct pack<PlayerPersistData> {
      template <typename Stream>
      packer<Stream>& operator()(
        msgpack::packer<Stream>& o, PlayerPersistData const& v) const {
        o.pack_array(10 + INVENTORY_SIZE * 2);
        o.pack_fix_uint32(v.id);
        o.pack_fix_uint32(v.gold);
        o.pack_fix_uint32(v.savedGold);
        o.pack_fix_uint32(v.level);
        o.pack_fix_uint32(v.currentHP);
        o.pack_fix_uint32(v.currentMP);
        o.pack_fix_uint32(v.currentExperience);
        o.pack(v.rootd);
        o.pack_fix_uint32(v.positionX);
        o.pack_fix_uint32(v.positionY);
        for (int i = 0; i < INVENTORY_SIZE; i++) {
          InventoryElementData inv = {0, 0, 0};
          if (v.inventory.size() > i) {
            inv = v.inventory[i];
          }
          o.pack(inv);
        }
        for (int i = 0; i < INVENTORY_SIZE; i++) {
          InventoryElementData inv = {0, 0, 0};
          if (v.savedInventory.size() > i) {
            inv = v.savedInventory[i];
          }
          o.pack(inv);
        }
        return o;
      }
    };
  }}
}

FileManager::FileManager() : playerIdIndex(0){
  const SystemConfig& s = GC::getS();
  std::ofstream f;
  f.open(s.dbFile, std::fstream::app);
  f.close();
  indexFile.open(
    s.indexFile,
    std::fstream::in | std::fstream::out |
    std::fstream::binary | std::fstream::app);
  dbFile.open(
    s.dbFile,
    std::fstream::in | std::fstream::out
    | std::fstream::binary);

  getBufferSize();
  getBufferDbSize();
  indexFile.seekp(0, indexFile.beg);
  parseIndexFile();
}

void FileManager::parseIndexFile(){
  std::stringstream strStream;
  strStream << indexFile.rdbuf(); //read the file
  std::string str = strStream.str(); //str holds the content of the file

  for (
    playerIdIndex = 0;
    playerIdIndex * ifBufferSize < str.length();
    playerIdIndex ++) {
    int i = playerIdIndex * ifBufferSize;
    std::string buffer = str.substr(i, ifBufferSize);

    msgpack::object_handle oh = msgpack::unpack(buffer.data(), buffer.size());
    msgpack::object obj = oh.get();

    FileIndex b = obj.as<FileIndex>();
    std::string nick(b.nick);

    std::cout << nick << std::endl;
    indexList.insert(
      std::pair<std::string, FileIndex>(nick, b));
  }
}

void FileManager::getBufferSize() {
  std::stringstream ss;
  FileIndex index;

  msgpack::pack(ss, index);
  std::string const& str = ss.str();
  ifBufferSize = str.size();
}

void FileManager::getBufferDbSize() {
  PlayerPersistData data;
  data.rootd = {PlayerClass::WARRIOR, PlayerRace::ELF};
  std::stringstream ss;
  msgpack::pack(ss, data);

  dbBufferSize = ss.str().size();
}

void FileManager::create(
  const std::string& nick,
  const std::string& password,
  const PlayerRootData& rootd,
  const PositionData& position){
    if (checkIfNickExists(nick)) return;

    std::cout << "CREAND PLAYER:  " << playerIdIndex << std::endl;
    createIndex(nick, password);
    createData(rootd, position);
    playerIdIndex ++;
}

void FileManager::createIndex(
  const std::string& nick, const std::string& password) {
  FileIndex index;
  strncpy(index.nick, nick.c_str(), nick.size() + 1);
  strncpy(index.password, password.c_str(), password.size() + 1);
  index.playerId = playerIdIndex;

  indexList.insert(
      std::pair<std::string, FileIndex>(nick, index));

  msgpack::pack(indexFile, index);

  indexFile.flush();
  if ((dbFile.rdstate() & std::ifstream::failbit ) != 0)
    throw std::runtime_error(ERROR_WR_IFILE);
}

void FileManager::createData(
  const PlayerRootData& rootd,
  const PositionData& position) {
  const GlobalConfig& c = GC::get();

  PlayerPersistData data = {
    static_cast<size_t>(playerIdIndex),
    c.playerInitialGold,
    0,
    c.playerInitialLevel,
    0,
    0,
    0,
    rootd,
    position.x,
    position.y,
    c.defaultInventory,
    {}
  };
  /** position file */
  dbFile.seekp(dbBufferSize * playerIdIndex, std::ios_base::beg);
  msgpack::pack(dbFile, data);
  if ((dbFile.rdstate() & std::ifstream::failbit ) != 0)
    throw std::runtime_error(ERROR_WR_DBFILE);

  dbFile.flush();
}

bool FileManager::authenticate(
  const std::string& nick, const std::string& password) {
    if (!checkIfNickExists(nick)) return false;
    FileIndex& index = indexList.at(nick);
    std::string savedPassword(index.password);
    return savedPassword == password;
}

PlayerPersistData FileManager::getData(const std::string& nick) {
  std::vector<char> buffer(dbBufferSize);

  FileIndex& index = indexList.at(nick);
  dbFile.seekg(dbBufferSize * index.playerId, std::ios_base::beg);
  dbFile.read(buffer.data(), dbBufferSize);
  if ((dbFile.rdstate() & std::ifstream::failbit ) != 0)
    throw std::runtime_error(ERROR_R_DBFILE);

  msgpack::object_handle oh = msgpack::unpack(buffer.data(), buffer.size());
  msgpack::object obj = oh.get();
  PlayerPersistData b = obj.as<PlayerPersistData>();

  return b;
}

void FileManager::saveData(const std::string& nick, PlayerPersistData& data) {
  /** position file */
  FileIndex& index = indexList.at(nick);

  dbFile.seekp(dbBufferSize * index.playerId, std::ios_base::beg);

  msgpack::pack(dbFile, data);
  if ((dbFile.rdstate() & std::ifstream::failbit ) != 0)
    throw std::runtime_error(ERROR_WR_DBFILE);

  dbFile.flush();
}

bool FileManager::checkIfNickExists(const std::string& nick){
  return indexList.count(nick);
}

bool FileManager::getPlayerId(const std::string& nick, size_t& id) {
  if (!checkIfNickExists(nick)) return false;
  FileIndex& index = indexList.at(nick);
  id = index.playerId;
  return true;
}

FileManager::~FileManager(){
  indexFile.close();
  dbFile.close();
}
