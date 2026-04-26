#include "Shotgun.h"
#include <iostream>

Shotgun::Shotgun()
    : Weapon("Pusca", 20, 6, 300, 0.7, true) {}

Shotgun::Shotgun(const std::string& name, int damage, int maxAmmo, int price, double fireRate)
    : Weapon(name, damage, maxAmmo, price, fireRate, true) {}

Shotgun::Shotgun(const Shotgun& other) : Weapon(other) {}

Shotgun& Shotgun::operator=(const Shotgun& other) {
    if (this != &other)
        Weapon::operator=(other);
    return *this;
}

int Shotgun::shoot() {
    if (!hasAmmo()) return 0;
    setAmmo(getAmmo() - 1);
    return getDamage();
}

Weapon* Shotgun::clone() const { return new Shotgun(*this); }

std::string Shotgun::getType()        const { return "SHOTGUN"; }
std::string Shotgun::getDescription() const {
    return "Loveste TOATE benzile deodata. Nu trebuie sa tintesti exact.";
}

void Shotgun::display() const {
    std::cout << getType() << " " << *this << "\n"
              << "  Descriere: " << getDescription() << "\n";
}

std::ostream& operator<<(std::ostream& os, const Shotgun& s) {
    os << static_cast<const Weapon&>(s);
    return os;
}

std::istream& operator>>(std::istream& is, Shotgun& s) {
    is >> static_cast<Weapon&>(s);
    return is;
}
