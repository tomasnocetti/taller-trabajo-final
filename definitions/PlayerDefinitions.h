#ifndef __PLAYERDEF_H
#define __PLAYERDEF_H

#include "NPCDefinitions.h"
#include "MapDefinitions.h"
#include "EntityDefinitions.h"
#include "EquipmentDefinitions.h"
#include "ChatDefinitions.h"
#include <string>
#include <vector>

#define PLAYER_WIDTH 25
#define PLAYER_HEIGHT 48

typedef enum {
  HUMAN = 'H',
  ELF = 'E',
  GNOME = 'G',
  DWARF = 'D'
} PlayerRace;

MSGPACK_ADD_ENUM(PlayerRace)

typedef enum {
  MAGE = 'M',
  CLERIC = 'C',
  PALADIN = 'P', 
  WARRIOR = 'W'
} PlayerClass;

MSGPACK_ADD_ENUM(PlayerClass)

struct ResurrectionData{
  std::chrono::system_clock::time_point timeToResurrection;
  bool resurrect;
};

struct InventoryElementData{
  int amount;
  bool isEquiped;
  int itemId;
};

struct ExperienceData{
  size_t currentExperience;
  size_t maxLevelExperience;
  size_t minLevelExperience;
  MSGPACK_DEFINE(currentExperience, maxLevelExperience, minLevelExperience)
};

struct PlayerRootData {
  PlayerClass pclass;
  PlayerRace prace;
  MSGPACK_DEFINE(pclass, prace)
};

struct MainPlayerData {
  std::string nick;
  size_t id;
  size_t gold;
  size_t level;
  ExperienceData experience;
  PlayerRootData rootd;
  std::vector<InventoryElementData> inventory;
  HealthAndManaData points;
  PositionData position;
  MovementData movement;
  EquipmentData equipment;
  ChatData chat;
  MSGPACK_DEFINE(nick, id, gold, level, experience, rootd, inventory, 
    points, position, movement, equipment, chat)
};

struct OtherPlayersData {
  size_t id;
  PositionData position;
  MovementData movement;
  PlayerRootData rootd;
  EquipmentData equipment;
  HealthAndManaData healthAndMana;
  ResurrectionData resurrection;
  MSGPACK_DEFINE(id, position, rootd, equipment, healthAndMana)
};

struct DropItemData{
  PositionData position;
  int amount;
  int id;
  MSGPACK_DEFINE(position, id) 
};

struct PlayerGameModelData {
  MainPlayerData playerData;
  std::vector<EnemyData> npcs;
  std::vector<OtherPlayersData> otherPlayers;
  std::vector<DropItemData> drops;
  MSGPACK_DEFINE(playerData, npcs, otherPlayers, drops)
};

namespace msgpack {
  MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS) {
  namespace adaptor {

    template<>
    struct convert<InventoryElementData> {
      msgpack::object const& operator()(msgpack::object const& o, InventoryElementData& v) const {
          InventoryElementData b {
            o.via.array.ptr[0].as<std::int32_t>(),
            o.via.array.ptr[1].as<bool>(),
            o.via.array.ptr[2].as<std::int32_t>()
          };
          v = b;
          return o;
      }
    };

    template<>
    struct pack<InventoryElementData> {
      template <typename Stream>
      packer<Stream>& operator()(msgpack::packer<Stream>& o, InventoryElementData const& v) const {
        // packing member variables as an array.
        // std::cout << "ACA1: " << v.amount << std::endl;
        o.pack_array(3);
        o.pack_fix_uint32(v.amount);
        v.isEquiped ? o.pack_true() : o.pack_false();
        o.pack_fix_uint32(v.itemId);
        return o;
      }
    };
  }}
}

#endif
