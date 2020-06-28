#ifndef GAME_CRON_H
#define GAME_CRON_H

#include "../common/Thread.h"
#include "../common/BlockingQueue.h"
#include "instructions/Instruction.h"
#include "../DataDefinitions.h"
#include "GameDefinitions.h"
#include <vector>

/** Game Cron es la clase que se va a encargar de manejar todas las acciones del juego
 * que requieran continuidad en el tiempo. Es importante entender que GameCron
 * NO MODIFICA DIRECTAMENTE modelos. Este envia instrucciones a traves de la misma
 * BlockingQueue que usan los ClientProxies para mandar instrucciones.
 * Sigue siendo el GAME MODEL quien modifica a los modelos, y este le pasa un update
 * al GameCron de toda la info .
 *
 * EJ:
 *  * Movimiento de jugadores y NPC
 *  * Recuperar MANA
 *  * Revivir NPC o jugadores despues de determinado tiempo.
 */
class GameCron: public Thread {
  public:
    explicit GameCron(InstructionBQ& instructionQueue);
    GameCron(const GameCron&) = delete;
    GameCron& operator=(const GameCron&) = delete;
    GameCron&& operator=(GameCron&& other) = delete;
    ~GameCron();
    void run() override;
    CronBQ& getBQ();
    void stop();

  private:
    void runPlayersMovement(std::vector<OtherPlayersData>& players);
    void runNPCLogic(
      std::vector<EnemyData>& npcs,
      std::vector<OtherPlayersData>& players);
    void aliveNPCLogic(std::vector<OtherPlayersData>& players, EnemyData &npc);
    void moveNPC(
      size_t id,
      PositionData& npc,
      PositionData& follow);
    void NPCAttack(
      size_t npcId,
      PositionData& playerToAttack);
    void NPCReSpawn(size_t id);
    std::atomic<bool> running;
    InstructionBQ& instructionQueue;
    CronBQ cronBQ;
};

#endif
