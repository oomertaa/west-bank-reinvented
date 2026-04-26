#include "Shop.h"
#include "Pistol.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <iomanip>

Shop::Shop() : name("Magazin") {}

Shop::Shop(const std::string& name) : name(name) {}

Shop::Shop(const Shop& other) : name(other.name) {
   for (const Weapon* w : other.catalog)
      catalog.push_back(w->clone());
}

Shop& Shop::operator=(const Shop& other) {
   if (this != &other) {
      name = other.name;
      for (Weapon* w : catalog) delete w;
      catalog.clear();
      for (const Weapon* w : other.catalog)
         catalog.push_back(w->clone());
   }
   return *this;
}

Shop::~Shop() {
   for (Weapon* w : catalog) delete w;
}

void Shop::addWeapon(Weapon* weapon) {
   if (weapon) catalog.push_back(weapon);
}

void Shop::loadFromFile(const std::string& filename) {
   std::ifstream f(filename);
   if (!f.is_open()) return;
   std::string type;
   while (f >> type) {
      if (type[0] == '#') { f.ignore(1000, '\n'); continue; }
      std::string wname;
      int damage, maxAmmo, price;
      double fireRate;
      f >> wname >> damage >> maxAmmo >> price >> fireRate;
      if (type == "Pistol")
         catalog.push_back(new Pistol(wname, damage, maxAmmo, price, fireRate));
   }
}

bool Shop::purchase(int idx, Player& player) {
   if (idx < 0 || idx >= static_cast<int>(catalog.size())) return false;
   Weapon* w = catalog[idx];
   if (player.getMoney() < w->getPrice()) {
      std::cout << "Nu ai destui bani!\n";
      return false;
   }
   player.addMoney(-w->getPrice());
   player.addWeapon(w->clone());
   std::cout << "Ai cumparat " << w->getName() << "!\n";
   return true;
}

int Shop::getCatalogSize() const { return static_cast<int>(catalog.size()); }

std::string Shop::getName() const { return name; }

void Shop::printSeparator() const {
   for (int i = 0; i < 40; i++) std::cout << '-';
   std::cout << '\n';
}

void Shop::displayItem(int idx) const {
   const Weapon* w = catalog[idx];
   std::cout << "  [" << idx << "] " << std::left << std::setw(16) << w->getName()
             << " Dmg:" << std::setw(4) << w->getDamage()
             << " Mun:" << std::setw(4) << w->getMaxAmmo()
             << " Pret:$" << w->getPrice() << '\n';
}

std::ostream& operator<<(std::ostream& os, const Shop& s) {
   os << s.name << " (" << s.catalog.size() << " arme)";
   return os;
}

std::istream& operator>>(std::istream& is, Shop& s) {
   is >> s.name;
   return is;
}
