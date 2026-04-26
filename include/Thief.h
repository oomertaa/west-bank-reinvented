#pragma once
#include "Entity.h"

class Thief: public Entity {
private:
   int lane;
   int position;
   int maxPosition;
   int reward;
   int attackDamage;
   std::string weaponName;
   bool defeated;
   bool escaped;

public: 
   Thief();
   Thief(const std::string& name, int hp, int lane, int maxPosition, int reward, int attackDamage, const std::string& weaponName);
   Thief(const Thief& other);
   Thief& operator=(const Thief& other);
   ~Thief();

   int getLane() const override;
   int getPosition() const override;
   int getMaxPosition() const override;
   int getReward() const override;
   bool isDefeated() const override;
   bool hasEscaped() const override;
   int getAttackDamage() const override;
   std::string getWeaponName() const;

   void setLane(int l);
   void setPosition(int p);
   void setReward(int r);

   void advance() override;
   void markDefeated() override;
   void markEscaped() override;

   void display() const override;
   void takeDamage(int dmg) override;
   bool isAlive() const override;
   std::string getSymbol() const override;

   friend std::ostream& operator<<(std::ostream& os, const Thief& t);
   friend std::istream& operator>>(std::istream& is, Thief& t);
};