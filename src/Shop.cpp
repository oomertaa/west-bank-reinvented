#include "Shop.h"
#include "Pistol.h"
#include "Shotgun.h"
#include "Rifle.h"
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
   if (!f.is_open())
      throw std::runtime_error("Nu pot deschide: " + filename);
   for (Weapon* w : catalog) delete w;
   catalog.clear();
   
   std::string type;
   while(f >> type){
      if(type[0] == '#'){
         f.ignore(1000, '\n');
         continue;
      }
      int damage, maxAmmo, price;
      double fireRate;
      std::string name;

      f >> damage >> maxAmmo >> price >> fireRate;
      std::getline(f, name);
      if (!name.empty() && name[0] == ' ') name = name.substr(1);

      Weapon* w = nullptr;
      if(type == "Pistol")        w = new Pistol(name, damage, maxAmmo, price, fireRate);
      else if(type == "Shotgun")  w = new Shotgun(name, damage, maxAmmo, price, fireRate);
      else if(type == "Rifle")    w = new Rifle(name, damage, maxAmmo, price, fireRate);

      if(w) catalog.push_back(w);
   }
}

bool Shop::purchase(int idx, Player& player) {
   if (idx < 0 || idx >= static_cast<int>(catalog.size()))
      throw std::out_of_range("Index invalid pentru catalog");

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
    std::cout << "+----------------------------------------------------------+\n";
}

void Shop::displayItem(int idx) const {
   const Weapon* w = catalog[idx];
   std::cout << "| [" << (idx + 1) << "] " << w->getType()
            << " - " << w->getName()
            << "\n|     DMG:" << w->getDamage()
            << "  Munitie:" << w->getMaxAmmo()
            << "  Foc/s:" << w->getFireRate()
            << "  Pret: $" << w->getPrice();
   if (w->doesHitAllLanes()) std::cout << "  [TOATE BENZILE]";
   std::cout << "\n|     " << w->getDescription() << "\n";
   printSeparator();
}


void Shop::open(Player& player) {
    bool inShop = true;
    while (inShop) {
        system("cls");
        std::cout << "\n";
        printSeparator();
        std::cout << "|          " << name << "          |\n";
        printSeparator();
        std::cout << "|  Banii tai: $" << player.getMoney()
                  << std::string(42 - std::to_string(player.getMoney()).size(), ' ') << "|\n";
        printSeparator();

        if (catalog.empty()) {
            std::cout << "|  Magazinul este gol.                                     |\n";
            printSeparator();
        } else {
            for (int i = 0; i < static_cast<int>(catalog.size()); ++i)
                displayItem(i);
        }

        std::cout << "| [0] Iesi din magazin                                     |\n";
        printSeparator();
        std::cout << "Alegere: ";

        int choice = -1;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 0) {
            inShop = false;
        } else {
            try {
                if (purchase(choice - 1, player))
                    std::cout << "  Arma cumparata! Apasa Enter...";
                else
                    std::cout << "  Cumparare esuata. Apasa Enter...";
                std::cin.ignore();
                std::cin.get();
            } catch (const std::exception& e) {
                std::cout << "  Eroare: " << e.what() << "\n  Apasa Enter...";
                std::cin.ignore();
                std::cin.get();
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Shop& s) {
   os << s.name << " (" << s.catalog.size() << " arme)";
   return os;
}

std::istream& operator>>(std::istream& is, Shop& s) {
   is >> s.name;
   return is;
}
