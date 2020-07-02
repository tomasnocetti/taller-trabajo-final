#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <vector>
#include <string>
#include <stdio.h>
#include "GameCron.h"
#include "services/MapParser.h"
#include "responses/Response.h"
#include "ecs/Player.h"
#include "ecs/Npc.h"
#include "../DataDefinitions.h"
#include "definitions/EquationDefinitions.h"
#include <map>

class Player;
class NPC;

class GameModel{
  private:
    std::vector<std::unique_ptr<Entity>> margins;
    std::vector<std::unique_ptr<Entity>> cities;
    std::vector<DropItemData> drops;
    std::vector<EnemyData> npcs;
    std::map<size_t, std::unique_ptr<NPC>> npcMap;
    std::map<size_t, ResponseBQ&> clientsBQ;
    std::map<size_t, std::unique_ptr<Player>> players;
    std::vector<OtherPlayersData> otherPlayers;
    std::vector<std::unique_ptr<Entity>> priests;
    MapParser m;
    CronBQ& cronBQ;
    void parseMapData();
    bool checkCityCollisions(Entity &entity);
    unsigned int randomSeed;

  public:
    GameModel(char* mapPath, CronBQ& cronBQ);
    ~GameModel();
    GameModel(const GameModel&) = delete;
    GameModel& operator=(const GameModel&) = delete;
    /* Handle move DIRECTION instruction. */
    void move(size_t playerId, int x, int y);
    /* Handle stop_movement instruction */
    void stopMovement(size_t playerId);
    /* Handle playerSetCoords instruction.
    Chequea colisiones. Si lo puede mover, lo mueve, caso contrario el modelo
    permanece intalterado. */
    void playerSetCoords(size_t playerId, int x, int y);
    /* Handle equip instruction */
    void equipPlayer(size_t playerId, int inventoryPosition);
    /* Handle npcSetCoords instruction */
    void npcSetCoords(size_t playerId, int xPos, int yPos);
    /* Handle npcAttack instruction */
    void npcAttack(size_t npcId, int xPos, int yPos);
    /* Handle npcRespawn instruction */
    void npcRespawn(size_t npcId);
    /* Handle resurrect instruction */
    void resurrect(size_t playerId);
    /* Handle resurrectPlayer instruction - GameCron Instruction */
    void resurrectPlayer(size_t playerId);
    /* Handle increasePlayerMana instruction */
    void recover(size_t playerId);
    /* Handle meditate instruction */
    void meditate(size_t playerId);
    /* Handle increaseManaMeditation instruction - GameCron Instruction */
    void increaseManaByMeditation(size_t playerId);
    /* Agrega un jugador al juego activo con su respectiva BQ de comuncacion.
      Devuelve true si pudo o es valido, false de lo contrario. */
    bool authenticate(
      std::string& nick,
      ResponseBQ& responseBQ,
      size_t& playerId);
    /* Elimina al jugador del juego activo. */
    void deAuthenticate(size_t playerId);
    /* En base al id del jugador, va a armar una estructura con los datos
    necesarios para que dicho cliente updatee su modelo. */
    void generatePlayerModel(size_t id, PlayerGameModelData &modelData);
    void propagate();
    void generateOtherPlayersGameData();
    void generateNPCVector();
    /* Handle close instruction */
    void eraseClient(size_t playerId);
    /* Handle attack instruction */
    void attack(size_t playerId, int xPos, int yPos);
    bool checkEntityCollisions(LiveEntity &entity);
    void getRespawnPosition(PositionData &positionToRes, LiveEntity &entity);
    void addPlayerDrops(Player &player);
    void getDropPosition(PositionData &positionToRes);
    bool checkDropCollisions(PositionData &dropPossiblePos);
    void addNPCDrop(DropItemData &drop);
    /* Handle throwInventoryObj instruction */
    void throwInventoryObj(size_t playerId, size_t inventoryPosition);
    /* Handle pickUp instruction */
    void pickUpObj(size_t playerId);
};

#endif
