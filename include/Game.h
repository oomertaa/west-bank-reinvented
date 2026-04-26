#pragma once
#include "Player.h"
#include "Level.h"
#include <vector>
#include <string>

class Game{
   private:
      Player player;
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