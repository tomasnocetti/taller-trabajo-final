#ifndef CLIENT_INSTRUCTION_H
#define CLIENT_INSTRUCTION_H

#include "BaseInstruction.h"
#include "../ClientProxy.h"
#include <string>

class Instruction;
class ClientProxy;

class MoveInstruction: public Instruction {
  public:
    MoveInstruction(size_t id, std::string xDir, std::string yDir);
    MoveInstruction(const MoveInstruction&) = delete;
    MoveInstruction& operator=(const MoveInstruction&) = delete;
    MoveInstruction&& operator=(MoveInstruction&& other) = delete;
    void run(GameModel& game) override;

  private:
    size_t playerId;
    std::string xDir;
    std::string yDir;
};

class AuthInstruction: public Instruction {
  public:
    explicit AuthInstruction(ClientProxy& client, std::string nick);
    AuthInstruction(const AuthInstruction&) = delete;
    AuthInstruction& operator=(const AuthInstruction&) = delete;
    AuthInstruction&& operator=(AuthInstruction&& other) = delete;
    void run(GameModel& game) override;

  private:
    ClientProxy& client;
    std::string nick;
};

class CloseInstruction : public Instruction {
  public:
    explicit CloseInstruction(size_t id);
    CloseInstruction(const CloseInstruction&) = delete;
    CloseInstruction& operator=(const CloseInstruction&) = delete;
    CloseInstruction&& operator=(CloseInstruction&& other) = delete;
    void run(GameModel& game) override;

  private:
    size_t playerId;
};

class StopMovementInstruction : public Instruction {
  public:
    explicit StopMovementInstruction(size_t id);
    StopMovementInstruction(const StopMovementInstruction&) = delete;
    StopMovementInstruction& operator=(const StopMovementInstruction&) 
      = delete;
    StopMovementInstruction&& operator=(StopMovementInstruction&& other) 
      = delete;
    void run(GameModel& game) override;

  private:
    size_t playerId;
};

class AttackInstrucion : public Instruction {
  public:
    AttackInstrucion(size_t id, std::string xPos, std::string yPos);
    AttackInstrucion(const AttackInstrucion&) = delete;
    AttackInstrucion& operator=(const AttackInstrucion&) 
      = delete;
    AttackInstrucion&& operator=(AttackInstrucion&& other) 
      = delete;
    void run(GameModel& game) override;

  private:
    size_t playerId;
    int xPos;
    int yPos;
};

class EquipInstruction : public Instruction {
  public:
    EquipInstruction(size_t id, std::string inventoryPosition);
    EquipInstruction(const EquipInstruction&) = delete;
    EquipInstruction& operator=(const EquipInstruction&) 
      = delete;
    EquipInstruction&& operator=(EquipInstruction&& other) 
      = delete;
    void run(GameModel& game) override;

  private:
    size_t playerId;
    size_t inventoryPosition;
};

class ResurrectInstrucion : public Instruction {
  public:
    explicit ResurrectInstrucion(size_t id);
    ResurrectInstrucion(const ResurrectInstrucion&) = delete;
    ResurrectInstrucion& operator=(const ResurrectInstrucion&) 
      = delete;
    ResurrectInstrucion&& operator=(ResurrectInstrucion&& other) 
      = delete;
    void run(GameModel& game) override;

  private:
    size_t playerId;
};

class MeditateInstruction : public Instruction {
  public:
    explicit MeditateInstruction(size_t id);
    MeditateInstruction(const MeditateInstruction&) = delete;
    MeditateInstruction& operator=(const MeditateInstruction&) 
      = delete;
    MeditateInstruction&& operator=(MeditateInstruction&& other) 
      = delete;
    void run(GameModel& game) override;

  private:
    size_t playerId;
};

class ThrowObjInstruction : public Instruction {
  public:
    ThrowObjInstruction(size_t id, std::string inventoryPosition);
    ThrowObjInstruction(const ThrowObjInstruction&) = delete;
    ThrowObjInstruction& operator=(const ThrowObjInstruction&) 
      = delete;
    ThrowObjInstruction&& operator=(ThrowObjInstruction&& other) 
      = delete;
    void run(GameModel& game) override;

  private:
    size_t playerId;
    size_t inventoryPosition;
};

class PickUpInstruction : public Instruction {
  public:
    explicit PickUpInstruction(size_t id);
    PickUpInstruction(const PickUpInstruction&) = delete;
    PickUpInstruction& operator=(const PickUpInstruction&) 
      = delete;
    PickUpInstruction&& operator=(PickUpInstruction&& other) 
      = delete;
    void run(GameModel& game) override;

  private:
    size_t playerId;
};

class ListInstruction : public Instruction {
  public:
    explicit ListInstruction(size_t id);
    ListInstruction(const ListInstruction&) = delete;
    ListInstruction& operator=(const ListInstruction&) 
      = delete;
    ListInstruction&& operator=(ListInstruction&& other) 
      = delete;
    void run(GameModel& game) override;

  private:
    size_t playerId;
};

class SellInstruction : public Instruction {
  public:
    SellInstruction(size_t id, std::string itemNumber);
    SellInstruction(const SellInstruction&) = delete;
    SellInstruction& operator=(const SellInstruction&) 
      = delete;
    SellInstruction&& operator=(SellInstruction&& other) 
      = delete;
    void run(GameModel& game) override;

  private:
    size_t playerId;
    size_t itemNumber;
};

class BuyInstruction : public Instruction {
  public:
    BuyInstruction(size_t id, std::string itemNumber);
    BuyInstruction(const BuyInstruction&) = delete;
    BuyInstruction& operator=(const SellInstruction&) 
      = delete;
    BuyInstruction&& operator=(BuyInstruction&& other) 
      = delete;
    void run(GameModel& game) override;

  private:
    size_t playerId;
    size_t itemNumber;
};

#endif
