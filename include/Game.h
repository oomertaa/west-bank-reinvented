#include "Player.h"
#include "Level.h"
#include "Shop.h"
#include <vector>
#include <string>

class Game{
   private:
      Player player;
      std::vector<LevelConfig> levelConfigs;
      int currentLevelIdx;
      Shop shop;
      bool running;

      void loadConfig(const std::string& configFile);
      void loadLevels(const std::string& levelsFile);
      void showMainMenu();
      void showInstructions() const; //check
      void showStats() const;
      void showGameOver(bool won);
      void playCurrentLevel();

      static void clearScreen();
      static void printBanner();

   public:
      Game();
      Game(const std::string& configFile, const std::string& levelsFile, const std::string& weaponsFile);
      Game(const Game& other);
      Game& operator=(const Game& other);
      ~Game();
      
      void run();

      friend std::ostream& operator<<(std::ostream& os, const Game& g);
      friend std::istream& operator>>(std::istream& is, Game& g);
};