#include "Entity.h"
#include <algorithm>
#include <stdexcept>

Entity::Entity() : name("Necunoscut"), hp(1), maxHp(1) {}

Entity::Entity(const std::string& name, int hp) : name(name), hp(hp), maxHp(hp) {
   if (hp <= 0)
      throw std::invalid_argument("HP trebuie sa fie pozitiv");
}

Entity::Entity(const Entity& other) : name(other.name), hp(other.hp), maxHp(other.maxHp) {}

Entity::~Entity() {}

int Entity::getLane() const { return -1; }
int Entity::getPosition() const { return -1; }
int Entity::getMaxPosition() const { return -1; }
int Entity::getReward() const { return 0; }
bool Entity::isDefeated() const { return false; }
bool Entity::hasEscaped() const { return false; }
int Entity::getAttackDamage() const { return 0; }
void Entity::advance() {}
void Entity::markDefeated() {}
void Entity::markEscaped() {}

Entity& Entity::operator=(const Entity& other) {
   if (this != &other) {
      name = other.name;
      hp = other.hp;
      maxHp = other.maxHp;
   }
   return *this;
}

std::string Entity::getName() const {
   return name;
}
int Entity::getHp() const {
   return hp;
}
int Entity::getMaxHp() const {
   return maxHp;
}

void Entity::setName(const std::string& name) {
   this->name = name;
}
void Entity::setHp(int hp) {
   this->hp = std::max(0, hp);
}

void Entity::heal(int amount) {
   if (amount < 0)
      throw std::invalid_argument("Valoarea heal trebuie sa fie pozitiva");
   hp = std::min(maxHp, hp + amount);
}

std::ostream& operator<<(std::ostream& os, const Entity& e) {
   os << e.name << " " << e.hp << " " << e.maxHp;
   return os;
}

std::istream& operator>>(std::istream& is, Entity& e) {
   is >> e.name >> e.hp >> e.maxHp;
   if (e.hp < 0) e.hp = 0;
   if (e.maxHp < 1) e.maxHp = 1;
   return is;
}