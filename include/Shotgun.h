#pragma once
#include "Weapon.h"

class Shotgun: public Weapon {
public:
   Shotgun();
   Shotgun(const std::string& name, int damage, int maxAmmo, int price, double fireRate);
   Shotgun(const Shotgun& other);
   ~Shotgun();
   Shotgun& operator=(const Shotgun& other);

   int shoot() override;
   Weapon* clone() const override;
   std::string getType() const override;
   std::string getDescription() const override;
   void display() const override;

   friend std::ostream& operator<<(std::ostream& os, const Shotgun& p);
   friend std::istream& operator>>(std::istream& is, Shotgun& p);
};