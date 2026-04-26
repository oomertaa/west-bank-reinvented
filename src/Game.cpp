#include "Game.h"
#include "Thief.h"
#include "Pistol.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <windows.h>


//TEMPORAR
static constexpr int MAX_THIEVES = 5;
static constexpr int MOVE_INTERVAL_MS = 1500;
static constexpr int SPAWN_INTERVAL_MS = 2000;
static constexpr int MAX_ESCAPED = 3;
static constexpr int THIEF_BASE_HP = 5;
static constexpr int THIEF_REWARD = 50;
static constexpr int MAX_POSITION = 8;

void Game::clearScreen() {
   system("cls");
}

void Game::printBanner() {
   clearScreen();
   for (int i = 0; i < 20; i++){
      std::cout << "=";
   }
   std::cout << "\n";
   std::cout << " W E S T B A N K\nJoc de actiune cum nu ati mai vazut.\n";
   for (int i = 0; i < 20; i++){
      std::cout << "=";
   }
   std::cout << "\n";
}

Game::Game() : player("Sheriff", 100, 500), currentLevelIdx(0), running(false), gameStarted(false) {
   shop.addWeapon(new Pistol("Pistol Îmbunătățit", 20, 15, 200, 1.5));
}

Game::Game(const std::string& configFile, const std::string& levelsFile)
   : player("Sheriff", 100, 500), currentLevelIdx(0), running(false), gameStarted(false){
      loadConfig(configFile);
      loadLevels(levelsFile);
   }

Game::~Game() {}

Game::Game(const Game& other) : player(other.player), levelConfigs(other.levelConfigs), currentLevelIdx(other.currentLevelIdx), running(other.running), gameStarted(other.gameStarted) {}

Game& Game::operator=(const Game& other) {
   if(this != &other) {
      player = other.player;
      levelConfigs = other.levelConfigs;
      currentLevelIdx = other.currentLevelIdx;
      running = other.running;
      gameStarted = other.gameStarted;
   }
   return *this;
}

void Game::loadConfig(const std::string& configFile) {
   std::ifstream f(configFile);
   if(!f.is_open())
      throw std::runtime_error("nu se poate deschide: " + configFile);
   std::string key, line;
   std::string pName = "Sherrif";
   int pHp = 100, pMoney = 500;

   while(f >> key) {
      if (key[0] == '#') { 
         f.ignore(1000, '\n'); 
         continue;
      }
      if(key == "player_name") f >> pName;
      else if(key == "player_hp") f >> pHp;
      else if(key == "player_start_money") f >> pMoney;
      else f.ignore(1000, '\n');
   }
   player = Player(pName, pHp, pMoney);
}

/*to finish*/void Game::loadLevels(const std::string& levelsFile) {
   std::ifstream f(levelsFile);
    if (!f.is_open())
        throw std::runtime_error("Nu pot deschide: " + levelsFile);
   levelConfigs.clear();
   std::string token;
   while (f >> token) {
      if(token[0] == '#') {
         f.ignore(1000, '\n');
         continue;
      }
      //TODO reading after writing classes
   }
}

void Game::showInstructions() const {
   clearScreen();
   for (int i = 0; i < 20; i++){
      std::cout << "=";
   }
   std::cout << "  INSTRUCTIUNI\n";
   for (int i = 0; i < 20; i++){
      std::cout << "=";
   }
   std::cout << "\n"
            << "  Hotii apar intr-o singura banda si avanseaza spre tine. Nu impusca ostaticii!\n"

            << "  TASTE DE TRAGERE:\n"
            << "    A  sau  <-  =  Banda STANGA\n"
            << "    S  sau  sageata-sus    =  Banda MIJLOC\n"
            << "    D  sau  -> =  Banda DREAPTA\n\n"
            << "  ALTE TASTE:\n"
            << "    R  ->  Reincarcare arma\n"
            << "    Q  ->  Parasesti nivelul (pierde)\n\n"
            << "  TIPURI DE HOTI:\n"
            << "    [H]  Bandit \n"
            << "    [B!] Boss\n\n"
            << "    [0] Ostatic(nu il impusca)\n\n"
            << "  ARME:\n"
            << "    PISTOL  - precis, rata de foc buna\n"
            << "    SHOTGUN - loveste TOATE benzile deodata!\n"
            << "    RIFLE   - daune foarte mari, munitie putina\n\n"
            << "  Castigi bani eliminand hoti. Intre niveluri poti\n"
            << "  cumpara arme mai bune din magazin.\n\n";
   for (int i = 0; i < 20; i++){
      std::cout << "=";
   }
   std::cout << "  Apasa Enter pentru a te intoarce...\n";
   std::cin.ignore();
   std::cin.get();
}   

void Game::showStats() const {
   clearScreen();
   for (int i = 0; i < 20; i++){
      std::cout << "=";
   }
   std::cout << " Statistici Jucator\n";
   for (int i = 0; i < 20; i++){
      std::cout << "=";
   }
   player.display();
   for (int i = 0; i < 20; i++){
      std::cout << "=";
   }
   std::cout<< "  Nivel curent: " << (currentLevelIdx + 1) << "/" << levelConfigs.size() << "\n";
   for (int i = 0; i < 20; i++){
      std::cout << "=";
   }
   std::cout << "Apasa Enter..\n";
   std::cin.ignore();
   std::cin.get();
}

void Game::showGameOver(bool won) {
   clearScreen();
   for (int i = 0; i < 20; i++){
      std::cout << "*";
   }
   if(won) {
      std::cout << "Felicitari! Ai supravietuit!\nScor final: " << player.getScore() << " puncte\n";
   } else {
      std::cout << "Ai pierdut! Mai incearca o data!\n Scor final: " << player.getScore() << " puncte\n";
   }
   for (int i = 0; i < 20; i++){
      std::cout << "*";
   }
   std::cout << "Apasa Enter pentru a te intoarce la meniu...\n";
   std::cin.ignore();
   std::cin.get();
   running = false;
   gameStarted = false;
}

void Game::playLevel(){
   std::unique_ptr<Thief> currentThief;
   int thievesSpawned = 0;
   int thievesDefeated = 0;
   int thievesEscaped = 0;
   std::string lastMessage;

   static std::mt19937 rng(std::random_device{}());
   auto randomLane = [&]() {
      return std::uniform_int_distribution<int>(0, 2)(rng);
   };

   auto spawnNext = [&]() {
      if(thievesSpawned >= MAX_THIEVES) return;
      int lane = randomLane();
      ++thievesSpawned;
      currentThief = std::make_unique<Thief>("Thief", THIEF_BASE_HP, lane, MAX_POSITION, THIEF_REWARD, 15, "Pistol");
      const char* laneNames[] = {"STANGA", "MIJLOC", "DREAPTA"};
      lastMessage = "A aparut un hot in banda " + std::string(laneNames[lane]) + "!";
   };

   auto handleShot = [&](int targetLane) {
      int dmg = player.shoot();
      if (dmg == 0) {
         return;
      }
      if (!currentThief) {
         lastMessage = "Nicio tinta!"; return;
      }
      if (targetLane == currentThief->getLane()) {
         currentThief->takeDamage(dmg);
         if (!currentThief->isAlive()) {
            lastMessage = "Hot eliminat! Ai castigat " + std::to_string(currentThief->getReward()) + " bani!";
            player.addMoney(currentThief->getReward());
            player.addScore(currentThief->getReward()*2);
            currentThief.reset();
            ++thievesDefeated;
         } else {
            lastMessage = "Lovit! HP hot:" + std::to_string(currentThief->getHp());
         }
      } else {
         lastMessage = "Ai ratat! Hotul e in alta banda!";
      }
   };

   auto updateThief = [&]() {
      if (!currentThief) 
         return;
      currentThief->advance();
      if (currentThief->getPosition() == 0) {
         // de adaugat damage player pe viitor
         lastMessage = "Hotul a evadat!";
         currentThief.reset();
         ++thievesEscaped;
      }
   };


   //Render
   const int W = 14;
   const std::string sep = "+" + std::string(W, '-') + "+" + std::string(W, '-') + "+" + std::string(W, '-') + "+";
   const std::string hdr = std::string(W*3+2, '=') + "+";


   auto center = [&](const std::string& s) {
      int padding = (W - (int)s.size()) / 2;
      return std::string(std::max(0, padding), ' ') + s + std::string(std::max(0, W - (int)s.size() - padding), ' ');
   };

   auto buildLaneRow = [&](int row) -> std::string {
      std::string cells[3] = {std::string(W, ' '), std::string(W, ' '), std::string(W, ' ')};
      
      if (currentThief) {
         int entityRow = currentThief->getMaxPosition() - currentThief->getPosition();
         if (entityRow == row) {
            int lane = currentThief->getLane();
            std::string info = currentThief->getSymbol() + std::to_string(currentThief->getHp()) + "HP";
            int pad = (W - (int)info.size()) / 2;
            if (pad < 0) pad = 0;
            cells[lane] = std::string(pad, ' ') + info + std::string(W - pad - (int)info.size(), ' ');
         }
      }

      if (row == MAX_POSITION) {
         for (int i = 0; i < 3; i++) {
            std::string p = "   [J]    ";
            int pad = (W - (int)p.size()) / 2;
            cells[i] = std::string(std::max(0, pad), ' ') + p + std::string(std::max(0, W - (int)p.size() - pad), ' ');
         }
      }
      return "|" + cells[0] + "|" + cells[1] + "|" + cells[2] + "|";
   };

   auto render = [&]() {
        COORD coord{0,0};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        std::cout << hdr << "\n";
        std::cout << "  W E S T B A N K"
                  << "  |  HP: " << player.getHp() << "/" << player.getMaxHp()
                  << "  |  $" << player.getMoney()
                  << "  |  Scor: " << player.getScore() << "\n";
        std::cout << hdr << "\n";
        std::cout << "|" << center("STANGA") << "|" << center("MIJLOC") << "|" << center("DREAPTA") << "|\n";
        std::cout << sep << "\n";

        for (int row = 0; row <= MAX_POSITION; ++row)
            std::cout << buildLaneRow(row) << "\n";

        std::cout << sep << "\n";

        auto w = player.getCurrentWeapon();
        if (w) {
            std::cout << "  Arma: " << std::left << std::setw(16) << w->getName()
                      << " | Munitie: " << w->getAmmo() << "/" << w->getMaxAmmo()
                      << " | Tip: " << w->getType() << "          \n";
        }

        std::cout << "  [A/Stg] Stanga  [S/Sus] Mijloc  [D/Dr] Dreapta  [R] Reincarc  [Q] Iesi\n";
        std::cout << hdr << "\n";
        std::cout << "  Hoti: " << thievesSpawned << "/" << MAX_THIEVES
                  << " | Eliminati: " << thievesDefeated
                  << " | Scapati: " << thievesEscaped << "/" << MAX_ESCAPED
                  << "                    \n";
        std::cout << "  " << std::left << std::setw(56) << lastMessage << "\n";
        std::cout << hdr << "\n";
    };

    auto isComplete = [&]() {
        return thievesDefeated+thievesEscaped >= MAX_THIEVES;
    };
    auto isFailed = [&]() {
        return thievesEscaped >= MAX_ESCAPED;
    };

    // joc
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo{1, FALSE};
    SetConsoleCursorInfo(hOut, &cursorInfo);
    system("cls");

    auto lastMoveTime = std::chrono::steady_clock::now();
    auto lastSpawnTime = std::chrono::steady_clock::now();
    spawnNext();

    bool quit = false;
   while(!isComplete() && !isFailed() && player.isAlive() && !quit) {
      if (_kbhit()) {
         int key = _getch();
         int targetLane = -1;

         if (key == 0 || key == 224) {
               int key2 = _getch();
               if      (key2 == 75) targetLane = 0;
               else if (key2 == 72) targetLane = 1;
               else if (key2 == 77) targetLane = 2;
         } else {
               char c = static_cast<char>(tolower(key));
               if      (c == 'a') targetLane = 0;
               else if (c == 's') targetLane = 1;
               else if (c == 'd') targetLane = 2;
               else if (c == 'r') { player.reload(); lastMessage = "Arma reincarcata!"; }
               else if (c == 'q') { lastMessage = "Ai parasit nivelul."; quit = true; }
         }

         if (targetLane >= 0) 
               handleShot(targetLane);
      }

      auto now = std::chrono::steady_clock::now();

      if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMoveTime).count() >= MOVE_INTERVAL_MS) {
         updateThief();
         lastMoveTime = now;
      }

      if(!currentThief && thievesSpawned < MAX_THIEVES) {
         if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastSpawnTime).count() >= SPAWN_INTERVAL_MS) {
            spawnNext();
            lastSpawnTime = now;
         }
      }

      render();
      Sleep(80);
   }

   cursorInfo.bVisible = TRUE;
   SetConsoleCursorInfo(hOut, &cursorInfo);
   clearScreen();

   if(quit || !player.isAlive() || isFailed()) {
      showGameOver(false);
      return;
   }


   std::cout << "Nivel completat! Ai eliminat " << thievesDefeated << "\n" << "Scor: " << player.getScore() << "\n"
             << "Apasa Enter pentru a continua...\n";
   std::cin.ignore();
   std::cin.get();
   gameStarted = false;
}

void Game::demonstratePolymorphism() {
   clearScreen();
   std::cout << "Demonstrare Polimorfism:\n";
   std::cout << "\n Colectie de Entity* cu tipuri diferite:\n\n";

   Thief t1("Thief", 4, 0, 8, 50, 15, "Pistol");
   Thief t2("Thief", 6, 1, 6, 50, 15, "Pistol");
   Player p1("Sheriff", 100, 500);

   std::vector<Entity*> entities = {&t1, &t2, &p1};

   for(auto* e: entities) {
      
      std::cout << "Simbol: " << e->getSymbol() << " -> ";
      e->display();
      std::cout << " Apel takeDamage(5) virtual.. \n";
      e->takeDamage(5);
      std::cout << " HP dupa damage: " << e->getHp() << "\n";
      std::cout << "-----------------------------\n";
   }

   std::cout << "\n Apel operator<< (prin referinta la Entity):\n";
   for(auto* e: entities) {
      std::cout << " " << e->getName() << "viu= " << (e->isAlive() ? "Da" : "Nu") << "\n";
   }

   std::cout << "Apasa Enter pentru a continua...\n";
   std::cin.ignore();
   std::cin.get();
}


void Game::showInventory() {
   while (true) {
      clearScreen();
      for (int i = 0; i < 20; i++) std::cout << "=";
      std::cout << " Inventar\n";
      for (int i = 0; i < 20; i++) std::cout << "=";
      std::cout << "\n";

      const auto& inv = player.getInventory();
      if (inv.empty()) {
         std::cout << "  Nu ai nicio arma!\n";
      } else {
         for (int i = 0; i < static_cast<int>(inv.size()); ++i) {
            std::string prefix = (i == player.getCurrentWeaponIdx()) ? " > " : "   ";
            std::cout << prefix << "[" << (i + 1) << "] " << inv[i]->getName()
                      << " | DMG: " << inv[i]->getDamage()
                      << " | Munitie: " << inv[i]->getAmmo() << "/" << inv[i]->getMaxAmmo()
                      << " | Tip: " << inv[i]->getType() << "\n";
         }
      }

      for (int i = 0; i < 20; i++) std::cout << "=";
      std::cout << "\n  Introdu numarul armei pentru a o echipa, sau 0 pentru a iesi: ";

      int choice = -1;
      std::cin >> choice;
      if (std::cin.fail()) {
         std::cin.clear();
         std::cin.ignore(1000, '\n');
         continue;
      }
      if (choice == 0) break;
      int idx = choice - 1;
      if (idx < 0 || idx >= static_cast<int>(inv.size())) {
         std::cout << "  Index invalid! Apasa Enter...\n";
         std::cin.ignore(); std::cin.get();
         continue;
      }
      player.switchWeapon(idx);
      std::cout << "  Echipat: " << inv[idx]->getName() << "! Apasa Enter...\n";
      std::cin.ignore(); std::cin.get();
   }
}

void Game::showMainMenu() {
    while (running) {
        printBanner();
        std::cout << "\n"
                  << "  [1] " << (gameStarted ? "Continua" : "Joc Nou") << "\n"
                  << "  [2] Statistici\n"
                  << "  [3] Shop\n"
                  << "  [4] Inventar\n"
                  << "  [5] Instructiuni\n"
                  << "  [6] Demo Polimorfism\n"
                  << "  [0] Iesire\n\n";
        for (int i = 0; i < 20; i++){
            std::cout << "=";
        }
        std::cout << "  Alegere: ";

        int choice = -1;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        try {
            switch (choice) {
            case 1:
                if (!gameStarted) {
                    player = Player("Sheriff", 100, 500);
                    gameStarted = true;
                }
                playLevel();
                break;
            case 2:
                showStats();
                break;
            case 3:
                shop.open(player);
                break;
            case 4:
                showInventory();
                break;
            case 5:
                showInstructions();
                break;
            case 6:
                demonstratePolymorphism();
                break;
            case 0:
                running = false;
                break;
            default:
                std::cout << "  Optiune invalida!\n";
                std::cin.ignore(); std::cin.get();
                break;
            }
        } catch (const std::exception& e) {
            std::cerr << "  Eroare: " << e.what() << "\n  Apasa Enter...";
            std::cin.ignore();
            std::cin.get();
        }
    }
}

void Game::run() {
   running = true;
   showMainMenu();
   clearScreen();
   std::cout << " Salutare, pistolar!!\n";
}

std::ostream& operator<<(std::ostream& os, const Game& g) {
   os << "Game | " << g.player; 
   return os;
}


std::istream& operator>>(std::istream& is, Game& g) {
   is >> g.player;
   return is;
}



