#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <vector>
#include <string>
#include <stdio.h>
#include "../common/BlockingQueue.h"
#include "../DataDefinitions.h"
#include "Player.h"
#include <map>

class Player;
using UpdateClientBQ = FixedBlockingQueue<PlayerGameModelData>;

class GameModel{
  private:
    std::map<size_t, UpdateClientBQ&> clientsBQ;
    std::vector<EnemyData> npcs;
    std::map<size_t, std::unique_ptr<Player>> players;
    std::vector<OtherPlayersData> otherPlayers;
    MapData map;
    // vector de entidades como son margenes del mapa
  public:
    GameModel();
    ~GameModel();
    GameModel(const GameModel&) = delete;
    GameModel& operator=(const GameModel&) = delete;
    /* Handle move instruction.
    Chequea colisiones. Si lo puede mover, lo mueve, caso contrario el modelo
    permanece intalterado. */
    void move();
    /* Agrega un jugador al juego activo con su respectiva BQ de comuncacion.
      Devuelve true si pudo o es valido, false de lo contrario. */
    bool authenticate(std::string& nick, UpdateClientBQ& clientBQ, size_t& playerId);
    /* Elimina al jugador del juego activo. */
    void deAuthenticate(size_t playerId);
    /* En base al id del jugador, va a armar una estructura con los datos 
    necesarios para que dicho cliente updatee su modelo. */
    void generatePlayerModel(size_t id, PlayerGameModelData &modelData);
    void propagate();
    void generateOtherPlayersGameData();
};

#endif
