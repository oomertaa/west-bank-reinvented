#include "LevelConfig.h"

LevelConfig::LevelConfig()
   : levelNumber(1), maxThieves(5), moveIntervalMs(1500), spawnIntervalMs(3500),
     maxEscaped(3), thiefBaseHp(5), thiefReward(50), maxPosition(8) {}

LevelConfig::LevelConfig(int ln, int mt, int mi, int si, int me, int thp, int tr, int mp)
   : levelNumber(ln), maxThieves(mt), moveIntervalMs(mi), spawnIntervalMs(si),
     maxEscaped(me), thiefBaseHp(thp), thiefReward(tr), maxPosition(mp) {}

LevelConfig::LevelConfig(const LevelConfig& other)
   : levelNumber(other.levelNumber), maxThieves(other.maxThieves),
     moveIntervalMs(other.moveIntervalMs), spawnIntervalMs(other.spawnIntervalMs),
     maxEscaped(other.maxEscaped), thiefBaseHp(other.thiefBaseHp),
     thiefReward(other.thiefReward), maxPosition(other.maxPosition) {}

LevelConfig& LevelConfig::operator=(const LevelConfig& other) {
   if (this != &other) {
      levelNumber = other.levelNumber; maxThieves = other.maxThieves;
      moveIntervalMs = other.moveIntervalMs; spawnIntervalMs = other.spawnIntervalMs;
      maxEscaped = other.maxEscaped; thiefBaseHp = other.thiefBaseHp;
      thiefReward = other.thiefReward; maxPosition = other.maxPosition;
   }
   return *this;
}

LevelConfig::~LevelConfig() {}

int LevelConfig::getLevelNumber()     const { return levelNumber; }
int LevelConfig::getMaxThieves()      const { return maxThieves; }
int LevelConfig::getMoveIntervalMs()  const { return moveIntervalMs; }
int LevelConfig::getSpawnIntervalMs() const { return spawnIntervalMs; }
int LevelConfig::getMaxEscaped()      const { return maxEscaped; }
int LevelConfig::getThiefBaseHp()     const { return thiefBaseHp; }
int LevelConfig::getThiefReward()     const { return thiefReward; }
int LevelConfig::getMaxPosition()     const { return maxPosition; }

std::ostream& operator<<(std::ostream& os, const LevelConfig& cfg) {
   os << cfg.levelNumber << " " << cfg.maxThieves << " " << cfg.moveIntervalMs << " "
      << cfg.spawnIntervalMs << " " << cfg.maxEscaped << " " << cfg.thiefBaseHp << " "
      << cfg.thiefReward << " " << cfg.maxPosition;
   return os;
}

std::istream& operator>>(std::istream& is, LevelConfig& cfg) {
   is >> cfg.levelNumber >> cfg.maxThieves >> cfg.moveIntervalMs >> cfg.spawnIntervalMs
      >> cfg.maxEscaped >> cfg.thiefBaseHp >> cfg.thiefReward >> cfg.maxPosition;
   return is;
}
