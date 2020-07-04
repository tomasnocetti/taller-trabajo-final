#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <msgpack.hpp>
#include <fstream>
#include "../../DataDefinitions.h"

#define STR_LEN 30
#define INVENTORY_SIZE 9

#define ERROR_R_IFILE "Error reading Index File."
#define ERROR_WR_IFILE "Error reading Index File."
#define ERROR_R_DBFILE "Error reading DB File."
#define ERROR_WR_DBFILE "Error writing DB File."

struct PlayerPersistData {
  size_t id;
  size_t gold;
  size_t savedGold;
  size_t level;
  size_t currentHP;
  size_t currentMP;
  size_t currentExperience;
  PlayerRootData rootd;
  std::vector<InventoryElementData> inventory;
  std::vector<InventoryElementData> savedInventory;
  // PositionData position;

};

struct FileIndex {
  size_t playerId;
  char nick[STR_LEN];
  char password[STR_LEN];
};

class FileManager{
  private:
    std::string filename;
    std::fstream indexFile;
    std::fstream dbFile;
    std::map<std::string, FileIndex> indexList;
    int playerIdIndex;
    size_t ifBufferSize;
    size_t dbBufferSize;
    void parseIndexFile();
    void createIndex(
      const std::string& nick,
      const std::string& password);
    void createData(const PlayerRootData& rootd);
    void getBufferSize();
    void getBufferDbSize();
  public:
    FileManager();
    ~FileManager();
    /* Crea un nuevo jugador en caso de que el nickName este disponible. */
    void create(
      const std::string& nick,
      const std::string& password,
      const PlayerRootData& rootd);
    /* Devuelve verdadero si el usuario ya existe, falso caso contrario. */
    bool checkIfNickExists(const std::string& nick);
    /* Devuelve el objeto de persistencia, si nick no exite lanza error. */
    PlayerPersistData getData(const std::string& nick);
    /* Guarda la persistance data de un jugador */
    void saveData(const std::string& nick, PlayerPersistData& data);
    /* Autenticar */
    bool authenticate(const std::string& nick, const std::string& password);
    /* Get ID from Nick */
    bool getPlayerId(size_t& id);
};

#endif
