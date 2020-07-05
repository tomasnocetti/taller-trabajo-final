#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../definitions/EquationDefinitions.h"
#include "../definitions/Items.h"
#include "../GameModel.h"
#include "../services/FileManager.h"
#include <string>
#include <vector>

class Equation;

class Player : public LiveEntity{
  private:
    std::string nick;
    size_t gold;
    ExperienceData experience;
    PlayerRootData rootd;
    std::vector<InventoryElementData> inventory;
    std::vector<InventoryElementData> itemsInBank;
    size_t goldInBank;
    EquipmentData equipment;
    RightHandEquipmentSkills rightSkills;
    LeftHandEquipmentSkills leftSkills;
    BodyEquipmentSkills bodySkills;
    HeadEquipmentSkills headSkills;
    ResurrectionData resurrection;
    ChatData chat;
    friend struct RightHandItem;
    friend struct LeftHandItem;
    friend struct BodyItem;
    friend struct HeadItem;
    friend struct HealthPotion;
    friend struct ManaPotion;
    friend class GameModel;
    friend class Trader;
    friend class Priest;
    friend class Banker;
  public:
    Player(MainPlayerData& playerData, size_t id);
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    /* Cheque si la posición a la que se quiere atacar contiene un npc
    u otro jugador. Caso afirmativo, chequea que con el arma que tiene
    equipada el jugador, se llegue a la zona de ataque. Caso afirmativo,
    se procede a la lógica de esquivar el ataque. Si el ataque es esquivado,
    no se genera ningun daño en el enemigo, y el jugador no gana experiencia.
    Si el ataque no logra ser esquivado, se calcula el daño y se le suma
    la experiencia correspondiente al jugador. */
    bool attack(LiveEntity &entity, int xCoord, int yCoord) override;
    /* Se descuenta el daño recibido de los puntos de salud, luego 
    de haber calculado los puntos de defensa. */
    void rcvDamage(int &damage) override;
    /* Se añade experiencia al jugador, en base al ataque realizado y los 
    stats de la entidad atacada. */
    void addExperience(int &damage, size_t &otherLevel, int &otherHealth,
      int &otherMaxHealth);
    /* Recibe una posición correspondiente al vector del inventario,
    y equipa lo que haya en dicha posición. Si es una pócima, la toma,
    y descuenta en uno la cantidad de pócimas. Si es un arma, de ataque
    o de defensa, setea el booleano isEquiped en verdadero, y los otros
    en falso. */
    void equip(int inventoryPosition);
    void equipDefault();
    void drop();
    void setTimeToResurrect(double minDistanceToPriest);
    void setPlayerGameModelData(PlayerGameModelData &modelData);
    void setOtherPlayersData(OtherPlayersData &otherData);
    int calculateExcessGold();
    void recover();
    bool throwObj(
      size_t inventoryPosition, 
      InventoryElementData &itemToDrop, 
      PositionData &dropFirstPos);
    void meditate();
    void stopMeditating();
    bool pickUp(DropItemData &drop);
    bool addItemToInventory(InventoryElementData &item, int opt);
    bool inventoryIsFull(size_t opt);
    bool isAlive();
    void setDeadDefaults();
    bool eraseInventoryItem(size_t inventoryPosition, int opt);
    void sendMessage(MessageType type, std::string msg);
    void buy(size_t itemValue, size_t itemId);
    void sell(size_t inventoryPos, size_t itemValue);
    size_t inventoryItemId(size_t inventoryPosition, int opt);
    void heal();
    PlayerPersistData generatePersistData();
    void depositGold(size_t amount);
    void depositItem(size_t inventoryPos);
    void withdrawGold(size_t amount);
    void withdrawItem(size_t inventoryPos);
    bool specialWeapon(size_t rightHandId);
    bool specialAttack(int xCoord, int yCoord);
    static std::unique_ptr<Player> createPlayer(
      PlayerPersistData& dataP, std::string& nick);
    static void setInitEquipment(EquipmentData &equipment, 
      PlayerRootData &root);   
    static void setExperienceData(size_t &level, ExperienceData &experience);
};

#endif
