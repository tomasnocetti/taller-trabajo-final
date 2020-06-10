#pragma once

#include "../DataDefinitions.h"

class MainPlayerController {
  public:
    MainPlayerController(const MainPlayerController&) = delete;
    MainPlayerController& operator=(const MainPlayerController&) = delete;
    MainPlayerController&& operator=(MainPlayerController&& other);
    ~MainPlayerController();
    void move();
    void atack();
  private:
    MainPlayerData data;
};
