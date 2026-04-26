#pragma once
#include "Thief.h"
#include "Player.h"
#include <chrono>
#include <string>
#include <memory>

struct LevelConfig {
   int levelNumber = 1;
   int maxThieves = 5;
   int moveIntervalMs = 1500;
   int spawnIntervalMs = 3500;
   int maxEscaped = 3;
   int thiefBaseHp = 5;
   int thiefReward = 50;
   int maxPosition = 8;
};

class Level {
private:
   LevelConfig config;
   std::unique_ptr<Entity> currentThief;
   int thievesSpawned;
   int thievesEscaped;
   std::string lastMessage;

   std::chrono::steady_clock::time_point lastMoveTime;
   std::chrono::steady_clock::time_point lastSpawnTime;

   void spawnNextThief();
   void handleShot(int lane, Player& player);
   void updateThief(Player& player);
   void render(const Player& player) const;
   std::string buildLaneRow(int row) const;

public:
   Level();
   explicit Level(const LevelConfig& config);
   Level(const Level& other);
   Level& operator=(const Level& other);
   ~Level();

   int getLevelNumber() const;
   bool isComplete() const;
   bool isFailed() const;
   int getThievesDefeated() const;
   int getThievesEscaped() const;

   void play(Player& player);


   friend std::ostream& operator<<(std::ostream& os, const Level& level);
   friend std::istream& operator>>(std::istream& is, Level& level);

};