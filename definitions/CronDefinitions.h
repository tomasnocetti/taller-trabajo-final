#ifndef __CRONDEF_H
#define __CRONDEF_H

#include "PlayerDefinitions.h"
#include "../common/BlockingQueue.h"
#include <vector>

struct CronGameModelData {
  std::vector<EnemyData> npcs;
  std::vector<OtherPlayersData> otherPlayers;
};

using CronBQ = FixedQueue<1, std::unique_ptr<CronGameModelData>>;

#endif 
