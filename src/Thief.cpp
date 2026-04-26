#include "Thief.h"
#include <iostream>
#include <algorithm>

Thief::Thief() : Entity("Thief", 4), lane(1), position(8), maxPosition(8), reward(50), attackDamage(15), weaponName("Pistol"), defeated(false), escaped(false) {}

Thief::Thief(const std::string& name, int hp, int lane, int maxPosition, int reward, int attackDamage, const std::string& weaponName)
   : Entity(name, hp), lane(lane), position(maxPosition), maxPosition(maxPosition), reward(reward), attackDamage(attackDamage), weaponName(weaponName), defeated(false), escaped(false) {}

Thief::Thief(const Thief& other) : Entity(other), lane(other.lane), position(other.position), maxPosition(other.maxPosition), reward(other.reward), attackDamage(other.attackDamage), weaponName(other.weaponName), defeated(other.defeated), escaped(other.escaped) {}

Thief::~Thief() {}

Thief& Thief::operator=(const Thief& other) {
   if (this != &other) {
      Entity::operator=(other);
      lane = other.lane;
      position = other.position;
      maxPosition = other.maxPosition;
      reward = other.reward;
      attackDamage = other.attackDamage;
      weaponName = other.weaponName;
      defeated = other.defeated;
      escaped = other.escaped;
   }
   return *this;
}

int Thief::getLane() const {
   return lane;
}
int Thief::getPosition() const {
   return position;
}
int Thief::getMaxPosition() const {
   return maxPosition;
}
int Thief::getReward() const {
   return reward;
}
bool Thief::isDefeated() const {
   return defeated;
}
bool Thief::hasEscaped() const {
   return escaped;
}
int Thief::getAttackDamage() const {
   return attackDamage;
}
std::string Thief::getWeaponName() const {
   return weaponName;
}

void Thief::setLane(int l) {
   lane = std::max(0, std::min(l, 2));
}

void Thief::setPosition(int p) {
   position = std::max(0, p);
}
void Thief::setReward(int r) {
   reward = std::max(0, r);
}


void Thief::advance() {
   if (position > 0)
      position--;
}
void Thief::markDefeated() {
   defeated = true;
}
void Thief::markEscaped() {
   escaped = true;
}

void Thief::display() const {
   const char* lanes[] = {"STANGA", "MIJLOC", "DREAPTA"};
   std::cout << "Hot: " << getName() << " HP: " << getHp() << "/" << getMaxHp() << " LANE: " << lanes[lane] << " POS: " << position << "/" << maxPosition << " ARMA: " << weaponName << "\n";
}

void Thief::takeDamage(int dmg) {
   setHp(getHp() - dmg);
   if (getHp() <= 0) {
      markDefeated();
   }
}

bool Thief::isAlive() const {
   return getHp() > 0;
}

std::string Thief::getSymbol() const {
   return "[H]";
}

std::ostream& operator<<(std::ostream& os, const Thief& t) {
   os << static_cast<const Entity&>(t)
      << " Banda:" << t.lane
      << " Poz:" << t.position
      << " Arma:" << t.weaponName;
   return os;
}

std::istream& operator>>(std::istream& is, Thief& t) {
   is >> static_cast<Entity&>(t) >> t.lane >> t.position >> t.reward >> t.weaponName >> t.attackDamage;
   t.maxPosition = t.position;
   return is;
}
