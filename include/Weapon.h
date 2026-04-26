#pragma once
#include <string>
#include <iostream>

class Weapon {
private:
   std::string name;
   int damage;
   int ammo;
   int maxAmmo;
   int price;
   double fireRate;
   bool hitsAllLanes;

protected:
   void setAmmo(int a);

public:
   Weapon();
   Weapon(const std::string& name, int damage, int maxAmmo, int price, double fireRate, bool hitsAllLanes = false);
   Weapon(const Weapon& other);
   Weapon& operator=(const Weapon& other);
   virtual ~Weapon();

   std::string getName() const;
   int getDamage() const;
   int getAmmo() const;
   int getMaxAmmo() const;
   int getPrice() const;
   double getFireRate() const;
   bool doesHitAllLanes() const;

   void setDamage(int dmg);
   void setPrice(int p);

   void reload();
   void reloadPartial(int ammo);
   bool hasAmmo() const;

   virtual int shoot() = 0;
   virtual std::string getType() const = 0;
   virtual std::string getDescription() const = 0;
   virtual void display() const = 0;
   virtual Weapon* clone() const = 0;

   friend std::ostream& operator<<(std::ostream& os, const Weapon& w);
   friend std::istream& operator>>(std::istream& is, Weapon& w);
};