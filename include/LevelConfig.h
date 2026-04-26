#pragma once
#include <iostream>
#include <string>

class LevelConfig {
private:
   int levelNumber;
   int maxThieves;
   int moveIntervalMs;
   int spawnIntervalMs;
   int maxEscaped;
   int thiefBaseHp;
   int thiefReward;
   int maxPosition;
public:
   LevelConfig();
   LevelConfig(int levelNumber, int maxThieves, int moveIntervalMs, int spawnIntervalMs,
               int maxEscaped, int thiefBaseHp, int thiefReward, int maxPosition);
   LevelConfig(const LevelConfig& other);
   LevelConfig& operator=(const LevelConfig& other);
   ~LevelConfig();

   int getLevelNumber() const;
   int getMaxThieves() const;
   int getMoveIntervalMs() const;
   int getSpawnIntervalMs() const;
   int getMaxEscaped() const;
   int getThiefBaseHp() const;
   int getThiefReward() const;
   int getMaxPosition() const;

   friend std::ostream& operator<<(std::ostream& os, const LevelConfig& cfg);
   friend std::istream& operator>>(std::istream& is, LevelConfig& cfg);
};
