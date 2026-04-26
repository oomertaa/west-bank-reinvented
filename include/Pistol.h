#pragma once
#include "Weapon.h"


class Pistol : public Weapon {
public:
   Pistol();
   Pistol(const std::string& name, int damage, int maxAmmo, int price, double fireRate);
   Pistol(const Pistol& other);
   Pistol& operator=(const Pistol& other);
   ~Pistol();

   int shoot() override;
   Weapon* clone() const override;
   std::string getType() const override;
   std::string getDescription() const override;
   void display() const override;

   friend std::ostream& operator<<(std::ostream& os, const Pistol& p);
   friend std::istream& operator>> (std::istream& is, Pistol& p);
};