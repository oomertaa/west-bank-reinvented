#pragma once
#include "Weapon.h"
#include "Player.h"
#include <vector>
#include <string>

class Shop {
private:
   std::string name;
   std::vector<Weapon*> catalog;

   void printSeparator() const;
   void displayItem(int idx) const;

public:
   Shop();
   explicit Shop(const std::string& name);
   Shop(const Shop& other);
   Shop& operator=(const Shop& other);
   ~Shop();

   void addWeapon(Weapon* weapon);
   void loadFromFile(const std::string& filename);
   bool purchase(int idx, Player& player);
   void open(Player& player);
   int getCatalogSize() const;
   std::string getName() const;

   friend std::ostream& operator<<(std::ostream& os, const Shop& s);
   friend std::istream& operator>>(std::istream& is, Shop& s);
};