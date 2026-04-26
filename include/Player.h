#pragma once
#include "Entity.h"
#include "Weapon.h"
#include <vector>

class Player : public Entity {
private:
   int money;
   int score;
   int currentWeaponIdx;
   std::vector<Weapon*> inventory;

public:
   Player();
   Player(const std::string& name, int hp, int money);
   Player(const Player& other);
   Player& operator=(const Player& other);
   ~Player();

   int getMoney() const;
   int getScore() const;
   int getCurrentWeaponIdx() const;
   Weapon* getCurrentWeapon() const;
   const std::vector<Weapon*>& getInventory() const;
   void setMoney(int m);
   void setScore(int s);

   void addMoney(int amount);
   void addScore(int amount);
   void addWeapon(Weapon* weapon);
   void switchWeapon(int idx);
   int shoot();
   void reload();
   bool hasWeapon() const;

   void display() const override;
   void takeDamage(int dmg) override;
   bool isAlive() const override;
   std::string getSymbol() const override;

   friend std::ostream& operator<<(std::ostream& os, const Player& p);
   friend std::istream& operator>>(std::istream& is, Player& p);
};