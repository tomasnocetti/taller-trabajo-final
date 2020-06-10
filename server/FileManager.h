#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <msgpack.hpp>
#include <fstream>

struct Index {
  char nick[32];
  int offsetPlayer;
  MSGPACK_DEFINE(nick, offsetPlayer)
};

struct Data{
  uint32_t x;
  int y;
  int oro;
  MSGPACK_DEFINE(x, y, oro)
};

class FileManager{
private:
  std::string filename;
  int offset;
public:
  FileManager();
  void read();
  /* Crea un nuevo jugador en caso de que el nickName este disponible. */
  void create(const char* nickName);
  /* Devuelve verdadero si el usuario ya existe, falso caso contrario. */
  bool checkIfNickExists(const char* nickName);
  /* Carga en un archivo la información del jugador. */
  void loadPlayerData(const char* nickName, struct Data data);
  /* Descarga del archivo la información correspondiente al jugador */
  void downloadPlayerData(const char* nickName);
  int getPlayerOffset(const char* nickName);
  ~FileManager();
};

#endif
