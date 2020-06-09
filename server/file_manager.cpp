#include "file_manager.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

FileManager::FileManager() : offset(0){}

void FileManager::create(const char* nickName){
  bool exist = checkIfNickExists(nickName);
  if (!exist){
    std::ofstream ofs("playersIndex.txt",std::ofstream::binary | 
    std::ofstream::app);
    Index index;
    strncpy(index.nick, nickName, sizeof(index.nick));
    index.offsetPlayer = offset;
    offset ++;
    msgpack::pack(ofs, index);
    std::cout << "Usuario " << nickName << " creado exitosamente." 
    << std::endl;
    ofs.close();
  }else{
    std::cout << "El nombre " << nickName << " no esta disponible." 
    << std::endl;
  }
}

bool FileManager::checkIfNickExists(const char* nickName){
  std::ifstream ifs("playersIndex.txt", std::ifstream::in);
  std::string buffer((std::istreambuf_iterator<char>(ifs)),
                        std::istreambuf_iterator<char>());
  msgpack::unpacker pac;
  pac.reserve_buffer(buffer.size());
  std::copy(buffer.begin(), buffer.end(), pac.buffer());
  pac.buffer_consumed(buffer.size());
  msgpack::object_handle oh;
  Index player; 
  while (pac.next(oh)){
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
    std::ofstream ofs("playersData.txt",std::ofstream::binary | 
    std::ofstream::app);
    msgpack::pack(ofs, data);
    ofs.close();
  }else{
    std::cout << "El usuario solicitado no se encuentra en la base de datos." 
    << std::endl;
  }
}

int FileManager::getPlayerOffset(const char* nickName){
  std::ifstream ifs("playersIndex.txt", std::ifstream::in);
  std::string buffer((std::istreambuf_iterator<char>(ifs)),
                        std::istreambuf_iterator<char>());
  msgpack::unpacker pac;
  pac.reserve_buffer(buffer.size());
  std::copy(buffer.begin(), buffer.end(), pac.buffer());
  pac.buffer_consumed(buffer.size());
  msgpack::object_handle oh;
  Index player; 
  while (pac.next(oh)){
    msgpack::object const& obj = oh.get();
    player = obj.as<Index>();
    std::cout << player.nick << std::endl;
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

FileManager::~FileManager(){}
