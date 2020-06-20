#ifndef __CRONDEF_H
#define __CRONDEF_H

#include "PlayerDefinitions.h"
#include "NPCDefinitions.h"
#include "../common/BlockingQueue.h"

struct CronGameModelData {
  std::vector<EnemyData> npcs;
  std::vector<OtherPlayersData> otherPlayers;
};

using CronBQ = FixedBlockingQueue<1, std::unique_ptr<CronGameModelData>>;

#endif
