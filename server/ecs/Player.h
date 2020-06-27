#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../definitions/EquationDefinitions.h"
#include "../GameModel.h"
#include <string>

class Equation;

class Player : public LiveEntity{
  private:
    size_t id;
    std::string nick;
    size_t gold;
    ExperienceData experience;
    PlayerRootData rootd;
    std::vector<InventoryElementData> inventory;
    MovementData movement;
    EquipmentData equipment;
    RightHandEquipmentSkills rightSkills;
    LeftHandEquipmentSkills leftSkills;
    BodyEquipmentSkills bodySkills;
    HeadEquipmentSkills headSkills;
    friend class GameModel;

  public:
    Player(MainPlayerData playerData, size_t id);
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
    /* Devuelve la cantidad de puntos de defensa en base a lo que tenga
    equipado el jugador */
    int defend();
    /* Se añade experiencia al jugador, en base al ataque realizado y los 
    stats de la entidad atacada. */
    void addExperience(int &damage, size_t &otherLevel, int &otherHealth,
      int &otherMaxHealth);
    static std::unique_ptr<Player> createPlayer(
      size_t id, 
      std::string nick, 
      PlayerRootData root);
    static void setClassSkills(SkillsData &skills, PlayerRootData &root);
    static void setRaceSkills(SkillsData &skills, PlayerRootData &root);  
    static void setInitEquipment(EquipmentData &equipment, 
      PlayerRootData &root);   
    static void setRighHandSkills(RightHandEquipmentSkills
      &rightSkills, RightHandEquipment &rightEquipment);
    static void setLeftHandSkills(LeftHandEquipmentSkills
      &leftSkills, LeftHandEquipment &leftEquipment); 
    static void setBodySkills(BodyEquipmentSkills
      &bodySkills, BodyEquipment &bodyEquipment); 
    static void setHeadSkills(HeadEquipmentSkills
      &headSkills, HeadEquipment &headEquipment);   
    static void setExperienceData(size_t &level, ExperienceData &experience);
    static void setPositionData(PlayerRootData &root, PositionData &position);
};

#endif
