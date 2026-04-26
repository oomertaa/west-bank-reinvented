#include "Player.h"
#include "Pistol.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

Player::Player() : Entity("Sheriff", 100), money(500), score(0), currentWeaponIdx(0) {}

Player::Player(const std::string& name, int hp, int money) : Entity(name, hp), money(money), score(0), currentWeaponIdx(0) {
   inventory.push_back(new Pistol());
}

Player::Player(const Player& other) 
   : Entity(other), money(other.money), score(other.score), currentWeaponIdx(other.currentWeaponIdx) {
   inventory.clear();
   for (const Weapon* w : other.inventory) {
      inventory.push_back(w->clone());
   }
}

Player& Player::operator=(const Player& other) {
   if (this != &other) {
      Entity::operator=(other);
      money = other.money;
      score = other.score;
      currentWeaponIdx = other.currentWeaponIdx;

      for (Weapon* w : inventory) {
         delete w;
      }
      inventory.clear();
      for (const Weapon* w : other.inventory) {
         inventory.push_back(w->clone());
      }
   }
   return *this;
}

Player::~Player() {
   for (Weapon* w : inventory) {
      delete w;
   }
}

int Player::getMoney() const {
   return money;
}
int Player::getScore() const {
   return score;
}
int Player::getCurrentWeaponIdx() const {
   return currentWeaponIdx;
}

Weapon* Player::getCurrentWeapon() const {
   if (inventory.empty())
      return nullptr;
   return inventory[currentWeaponIdx];
}

const std::vector<Weapon*>& Player::getInventory() const {
   return inventory;
}

void Player::setMoney(int m) {
   money = std::max(0, m);
}
void Player::setScore(int s) {
   score = std::max(0, s);
}

void Player::addMoney(int amount) {
   money += amount;
}
void Player::addScore(int amount) {
   score += amount;
}

void Player::addWeapon(Weapon* weapon) {
   if (weapon)
      inventory.push_back(weapon);
}

void Player::switchWeapon(int idx) {
   if (idx < 0 || idx >= static_cast<int>(inventory.size()))
      throw std::out_of_range("Index invalid pentru schimbarea armei");
   currentWeaponIdx = idx;
}

int Player::shoot() {
   Weapon* w = getCurrentWeapon();
   if (!w)
      return 0;
   if (!w->hasAmmo()) {
      std::cout << "Nu mai ai gloante! Reincarca!\n";
      return 0;
   }
   return w->shoot();
}

void Player::reload() {
   Weapon* w = getCurrentWeapon();
   if (w)
      w->reload();
}

bool Player::hasWeapon() const {
   return !inventory.empty();
}

void Player::display() const {
   std::cout << getName() << " HP: " << getHp() << "/" << getMaxHp() << " Bani: $" << money << " Scor: " << score << "\n";
   if (hasWeapon()) {
      std::cout << "Arma curenta: ";
      getCurrentWeapon()->display();
   }
   std::cout << "Inventar (" << inventory.size() << " arme):\n";
   for (int i = 0; i < static_cast<int>(inventory.size()); i++) {
      std::cout << " [" << i << "] ";
      inventory[i]->display();
   }
}

void Player::takeDamage(int dmg) {
   setHp(getHp() - dmg);
}
bool Player::isAlive() const {
   return getHp() > 0;
}
std::string Player::getSymbol() const {
   return "[P]";
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
   os << static_cast<const Entity&>(p)
      << " $:" << p.money
      << " Scor:" << p.score;
   return os;
}

std::istream& operator>>(std::istream& is, Player& p) {
   is >> static_cast<Entity&>(p) >> p.money >> p.score;
   return is;
}

