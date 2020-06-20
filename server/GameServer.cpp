#include "GameServer.h"


#include <utility>
#include <iostream>
#include <vector>

GameServer::GameServer(std::string& mapPath) :
  running(true),
  game(mapPath),
  cron(instructionQueue) {
    m.loadMap(mapPath);
}

GameServer::~GameServer(){}

void GameServer::init(){
  parseMapData();
  /* Cargar todo lo que el servidor necesite
    Cargar Mapa en memoria.
    Cargar Archivo con datos indexables del jugador.
    Cargar Definiciones.
  */
 
}

void GameServer::start(){
  ClientAcceptor acceptor(instructionQueue);
  acceptor.start();
  int i = 0;

  while (running && i<1000){
    i++;

    std::unique_ptr<Instruction> instruction;
    instructionQueue.try_front_pop(instruction);


    instruction->run(game);
    game.propagate();
  }
}

void GameServer::parseMapData() {
  game.setMapData(m.getMapData());
  std::vector<struct ObjectLayerData>& obj = m.getObjectLayers();

  for (size_t i = 0; i < obj.size(); i++){
    ObjectLayerData layer = obj[i];
    for (size_t j = 0; j < obj[i].objects.size(); j++){
      std::cout << obj[i].objects[j].x << std::endl;
      std::cout << obj[i].objects[j].y << std::endl;
      std::cout << obj[i].objects[j].width << std::endl;
      std::cout << obj[i].objects[j].height << std::endl;
    }
  }
}

void GameServer::close(){
  running = false;
}
