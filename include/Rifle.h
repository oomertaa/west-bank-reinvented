#pragma once
#include "Weapon.h"

class Rifle : public Weapon {
public:
   Rifle();
   Rifle(const std::string& name, int damage, int maxAmmo, int price, double fireRate);
   Rifle(const Rifle& other);
   ~Rifle();
   Rifle& operator=(const Rifle& other);

   int shoot() override;
   Weapon* clone() const override;
   std::string getType() const override;
   std::string getDescription() const override;
   void display() const override;

   friend std::ostream& operator<<(std::ostream& os, const Rifle& p);
   friend std::istream& operator>>(std::istream& is, Rifle& p);
};