#include "Rifle.h"
#include <iostream>

Rifle::Rifle()
    : Weapon("Pusca cu luneta", 45, 8, 400, 0.4, false) {}

Rifle::Rifle(const std::string& name, int damage, int maxAmmo, int price, double fireRate)
    : Weapon(name, damage, maxAmmo, price, fireRate, false) {}

Rifle::Rifle(const Rifle& other) : Weapon(other) {}

Rifle::~Rifle() {}

Rifle& Rifle::operator=(const Rifle& other) {
    if (this != &other)
        Weapon::operator=(other);
    return *this;
}

int Rifle::shoot() {
    if (!hasAmmo()) return 0;
    setAmmo(getAmmo() - 1);
    return getDamage();
}

Weapon* Rifle::clone() const { return new Rifle(*this); }

std::string Rifle::getType()        const { return "RIFLE"; }
std::string Rifle::getDescription() const {
    return "Daune foarte mari, munitie putina. Precis.";
}

void Rifle::display() const {
    std::cout << getType() << " " << *this << "\n"
              << "  Descriere: " << getDescription() << "\n";
}

std::ostream& operator<<(std::ostream& os, const Rifle& r) {
    os << static_cast<const Weapon&>(r);
    return os;
}

std::istream& operator>>(std::istream& is, Rifle& r) {
    is >> static_cast<Weapon&>(r);
    return is;
}



