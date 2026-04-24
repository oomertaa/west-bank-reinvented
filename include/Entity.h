#include <string>
#include <iostream>

class Entity {
private:
   std::string name;
   int hp;
   int maxHp;
   
protected:
   void heal(int amount);

public:
   Entity();
   Entity(const std::string& name, int hp);
   Entity(const Entity& other);
   Entity& operator=(const Entity& other);
   virtual ~Entity();

   std::string getName() const;
   int getHp() const;
   int getMaxHp() const;
   void setName(const std::string& name);
   void setHp(int hp);

   virtual void display() const = 0;
   virtual void takeDamage(int dmg) = 0;
   virtual bool isAlive() const = 0;
   virtual std::string getSymbol() const = 0;

   friend std::ostream& operator<<(std::ostream& os, const Entity& e);
   friend std::istream& operator>>(std::istream& is, Entity& e);
}