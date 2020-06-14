#include "LifeViewport.h"

LifeViewport::LifeViewport(SdlWindow& window, int x, int y, int w, int h) :
  SdlViewport(window, x, y, w, h) {}

void LifeViewport::init(SdlWindow& window) {
	this->manaBar.init(window, MANA_TEX, 
		BAR_X - X, MANA_BAR_Y - Y, BAR_W, BAR_H);
	this->healthBar.init(window, HEALTH_TEX, 
		BAR_X - X, HEALTH_BAR_Y - Y, BAR_W, BAR_H);  
}

void LifeViewport::paint() {
  fit();
  static int i = 300;
  int maxMana = 300, maxHealth = 300;
  this->manaBar.paint(i, maxMana);
  this->healthBar.paint(i, maxHealth);
  i--;
  if(i == 0)
  	i = 300;
}

LifeViewport::~LifeViewport() {}
