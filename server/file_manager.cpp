#include "file_manager.h"
#include <fstream>
#include <iostream>

FileManager::FileManager(const char* filePlayers) : offset(0),
  filename(filePlayers){}

void FileManager::create(const char* nickName){
  bool exist = checkIfNickExists(nickName);
  if (!exist){
    std::ofstream ofs(filename,std::ofstream::binary | std::ofstream::app);
    Index index;
    strcpy(index.nick, nickName);
    index.offsetPlayer = offset;
    offset ++;
    msgpack::pack(ofs, index);
    std::cout << "Usuario " << nickName << " creado exitosamente." << std::endl;
    ofs.close();
  }else{
    std::cout << "El nombre " << nickName << " no esta disponible." << std::endl;
  }
}

bool FileManager::checkIfNickExists(const char* nickName){
  std::ifstream ifs(filename, std::ifstream::in);
  std::string buffer((std::istreambuf_iterator<char>(ifs)),
                        std::istreambuf_iterator<char>());
  msgpack::unpacker pac;
  pac.reserve_buffer( buffer.size() );
  std::copy( buffer.begin(), buffer.end(), pac.buffer());
  pac.buffer_consumed( buffer.size() );
  msgpack::object_handle oh;
  Index player; 
  while (pac.next(oh)) {
    msgpack::object msg = oh.get();
    msgpack::object const& obj = oh.get();
    player = obj.as<Index>();
    if (strcmp(nickName, player.nick) == 0)
      return true;
  }
  return false;
}

void FileManager::loadPlayerData(const char* nickName, struct Data data){
  int exist = checkIfNickExists(nickName);
  if (exist){
    std::ofstream ofs("playersData.txt",std::ofstream::binary | std::ofstream::app);
    msgpack::pack(ofs, data);
    ofs.close();
  }else{
    std::cout << "El usuario solicitado no se encuentra en la base de datos." << std::endl;
  }
}

int FileManager::getPlayerOffset(const char* nickName){
  std::ifstream ifs(filename, std::ifstream::in);
  std::string buffer((std::istreambuf_iterator<char>(ifs)),
                        std::istreambuf_iterator<char>());
  msgpack::unpacker pac;
  pac.reserve_buffer( buffer.size() );
  std::copy( buffer.begin(), buffer.end(), pac.buffer() );
  pac.buffer_consumed( buffer.size() );
  msgpack::object_handle oh;
  Index player; 
  while (pac.next(oh)) {
    msgpack::object const& obj = oh.get();
    player = obj.as<Index>();
    if (strcmp(nickName, player.nick) == 0){
      return player.offsetPlayer;
    }
  }
  return 0;
}

void FileManager::downloadPlayerData(const char* nickName){
  std::ifstream ifs("playersData.txt", std::ifstream::in);
  int offset = getPlayerOffset(nickName);
  std::cout << offset << std::endl;
  ifs.seekg(offset*8);
  std::stringstream buffer;
  buffer << ifs.rdbuf();
  msgpack::unpacked upd;
  msgpack::unpack(upd, buffer.str().data(), buffer.str().size());
  std::cout << upd.get() << std::endl;
}

/*
void FileManager::downloadPlayerData(const char* nickName){
  std::ifstream ifs("playersData.txt", std::ifstream::in);
  std::string buffer((std::istreambuf_iterator<char>(ifs)),
                        std::istreambuf_iterator<char>());
  msgpack::unpacker pac;
  pac.reserve_buffer( buffer.size() );
  std::copy( buffer.begin(), buffer.end(), pac.buffer() );
  //std::cout << buffer.size() << std::endl;
  pac.buffer_consumed( buffer.size() );
  msgpack::object_handle oh;
  Data data;
  while (pac.next(oh)) {
    msgpack::object const& obj = oh.get();
    data = obj.as<Data>();
    std::cout << "La cantidad de oro disponible es: " << data.oro << std::endl;
    std::cout << "Posición x: " << data.x << std::endl;
    std::cout << "Posición y: " << data.y << std::endl;
  }
}
*/

FileManager::~FileManager(){}

/*
  std::ifstream ifs("players.dat",std::ifstream::binary);
  std::stringstream ss;
  ss << ifs.rdbuf();
  msgpack::object_handle oh = msgpack::unpack(ss.str().data(), ss.str().size());
  msgpack::object const& obj = oh.get();
  auto v2 = obj.as<Index>();
  std::cout << "Nick name: " << v2.nick << std::endl;
  std::cout << "Offset del jugador : " << v2.offsetPlayer << std::endl;
  */
 /*
  std::stringstream buffer;
  buffer << ifs.rdbuf();
  msgpack::unpacked upd;
  msgpack::unpack(upd, buffer.str().data(), buffer.str().size());
  std::cout << upd.get() << std::endl;
  buffer << ifs.rdbuf();
  msgpack::unpacked upd2;
  msgpack::unpack(upd2, buffer.str().data(), buffer.str().size());
  std::cout << upd2.get() << std::endl;
  */
 /*
  std::ifstream ifs("players.dat", std::ifstream::in);
  std::string buffer((std::istreambuf_iterator<char>(ifs)),
                      std::istreambuf_iterator<char>());
  msgpack::unpacked upd;
  std::size_t offset = 0;
  for (std::size_t i = 0; i != 3; ++i) {
    msgpack::unpack(upd, buffer.data(), buffer.size(), offset);
    std::cout << upd.get() << std::endl;
  }
  */