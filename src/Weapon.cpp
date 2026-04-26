#include "Weapon.h"
#include <algorithm>
#include <stdexcept>
#include <iomanip>

Weapon::Weapon() : name("Nicio arma"), damage(0), ammo(0), maxAmmo(0), price(0), fireRate(0.0), hitsAllLanes(false) {}

Weapon::Weapon(const std::string& name, int damage, int maxAmmo, int price, double fireRate, bool hitsAllLanes)
   : name(name), damage(damage), ammo(maxAmmo), maxAmmo(maxAmmo), price(price), fireRate(fireRate), hitsAllLanes(hitsAllLanes) {
      if (damage < 0 || maxAmmo < 0 || price < 0 || fireRate < 0.0)
         throw std::invalid_argument("Valorile damage, maxAmmo, price si fireRate trebuie sa fie pozitive");
   }

Weapon::Weapon(const Weapon& other) : name(other.name), damage(other.damage), ammo(other.ammo), maxAmmo(other.maxAmmo), price(other.price), fireRate(other.fireRate), hitsAllLanes(other.hitsAllLanes) {}

Weapon::~Weapon() {}

Weapon& Weapon::operator=(const Weapon& other) {
   if (this != &other) {
      name = other.name;
      damage = other.damage;
      ammo = other.ammo;
      maxAmmo = other.maxAmmo;
      price = other.price;
      fireRate = other.fireRate;
      hitsAllLanes = other.hitsAllLanes;
   }
   return *this;
}

std::string Weapon::getName() const {
   return name;
}
int Weapon::getDamage() const {
   return damage;
}
int Weapon::getAmmo() const {
   return ammo;
}
int Weapon::getMaxAmmo() const {
   return maxAmmo;
}
int Weapon::getPrice() const {
   return price;
}
double Weapon::getFireRate() const {
   return fireRate;
}
bool Weapon::doesHitAllLanes() const {
   return hitsAllLanes;
}

void Weapon::setDamage(int d) {
   damage = std::max(0, d);
}
void Weapon::setPrice(int p) {
   price = std::max(0, p);
}
void Weapon::setAmmo(int a) {
   ammo = std::max(0, std::min(a, maxAmmo));
}

void Weapon::reload() {
   ammo = maxAmmo;
}

void Weapon::reloadPartial(int a) {
   setAmmo(ammo + a);
}

bool Weapon::hasAmmo() const {
   return ammo > 0;
}

std::ostream& operator<<(std::ostream& os, const Weapon& w) {
   os << w.name << " " << w.damage << " " << w.ammo << " " << w.maxAmmo << " " << w.price << " " << w.fireRate << " " << w.hitsAllLanes;
   return os;
}

std::istream& operator>>(std::istream& is, Weapon& w) {
   is >> w.name >> w.damage >> w.ammo >> w.maxAmmo >> w.price >> w.fireRate >> w.hitsAllLanes;
   if (w.damage < 0) w.damage = 0;
   if (w.maxAmmo < 0) w.maxAmmo = 0;
   if (w.price < 0) w.price = 0;
   if (w.fireRate < 0.0) w.fireRate = 0.0;
   if (w.ammo < 0) w.ammo = 0;
   if (w.ammo > w.maxAmmo) w.ammo = w.maxAmmo;
   return is;
}