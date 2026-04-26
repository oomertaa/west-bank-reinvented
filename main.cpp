#include "include/Game.h"
#include <iostream>
#include <windows.h>

int main(){
   try {
      Game game;
      game.run();
   } catch (const std::exception& e) {
      std::cerr << "Eroare: " << e.what() << "\n";
      return 1;
   }
   return 0;
}