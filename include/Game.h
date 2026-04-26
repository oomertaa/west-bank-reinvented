#pragma once
#include "Player.h"
#include "Shop.h"
#include <vector>
#include <string>

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

class Game{
   private:
      Player player;
      Shop shop;
      std::vector<LevelConfig> levelConfigs;
      int currentLevelIdx;
      bool running;
      bool gameStarted;

      void loadConfig(const std::string& configFile);
      void loadLevels(const std::string& levelsFile);
      void showMainMenu();
      void showInstructions() const;
      void showStats() const;
      void showGameOver(bool won);
      void showInventory();
      void playLevel();
      void demonstratePolymorphism();

      static void clearScreen();
      static void printBanner();

   public:
      Game();
      Game(const std::string& configFile, const std::string& levelsFile);
      Game(const Game& other);
      Game& operator=(const Game& other);
      ~Game();
      
      void run();

      friend std::ostream& operator<<(std::ostream& os, const Game& g);
      friend std::istream& operator>>(std::istream& is, Game& g);
};