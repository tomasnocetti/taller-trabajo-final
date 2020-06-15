#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <vector>
#include <string>
#include <stdio.h>
#include "../DataDefinitions.h"
#include "Player.h"

class Player;

class GameModel{
  private:
    std::vector<EnemyData> npcs;
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::unique_ptr<OtherPlayersData>> otherPlayers;
    MapData map;
    // vector de entidades como son margenes del mapa
  public:
    GameModel();
    ~GameModel();
    GameModel(const GameModel&) = delete;
    GameModel& operator=(const GameModel&) = delete;
    /* Handle loadPlayer instruction. 
    Crea una instancia de Player, y le asigna
    los datos correspondientes a ese id. */
    bool loadPlayer(InstructionData &instruction);
    /* En base al id del jugador, va a armar una estructura con los datos 
    necesarios para que dicho cliente updatee su modelo. */
    void generatePlayerModel(size_t id, PlayerGameModelData &modelData);
    /* Handle move instruction.
    Chequea colisiones. Si lo puede mover, lo mueve, caso contrario el modelo
    permanece intalterado. */
    bool move(InstructionData &instruction);
    /* Devuelve verdadero si la instrucción modifico el modelo, falso
    caso contrario. */
    bool handleInstruction(InstructionData &instruction);
};

#endif
