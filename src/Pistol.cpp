#include "Pistol.h"
#include <iostream>

//const std::string& name, int damage, int maxAmmo, int price, double fireRate, bool hitsAllLanes = false
Pistol::Pistol() : Weapon("Pistol", 15, 12, 0, 1.5, false) {}

Pistol::Pistol(const std::string& name, int damage, int maxAmmo, int price, double fireRate) : Weapon(name, damage, maxAmmo, price, fireRate, false) {}

Pistol::Pistol(const Pistol& other) : Weapon(other) {}

Pistol::~Pistol() {}

Pistol& Pistol::operator=(const Pistol& other) {
   if (this != &other)
      Weapon::operator=(other);
   return *this;
}

int Pistol::shoot() {
   if (!hasAmmo())
      return 0;
   setAmmo(getAmmo() - 1);
   return getDamage();
}

Weapon* Pistol::clone() const {
   return new Pistol(*this);
}

std::string Pistol::getType() const {
   return "Pistol";
}
std::string Pistol::getDescription() const {
   return "Pistol basic. 12 gloante, rata de foc buna";
}

void Pistol::display() const {
   std::cout << getType() << " " << *this << "\n" << getDescription() << "\n";
}

std::ostream& operator<<(std::ostream& os, const Pistol& p) {
   os << static_cast<const Weapon&>(p);
   return os;
}

std::istream& operator>>(std::istream& is, Pistol& p) {
   is >> static_cast<Weapon&>(p);
   return is;
}
