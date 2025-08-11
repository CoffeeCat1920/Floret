#include "./include/raylib/raylib.h"
#include "./include/core/settings.h"
#include "./include/core/colors.h"
#include "include/world/tileMap.h"

class Game {
  
private:

  TileMap tileMap;

public:

  Game() : 
    tileMap("./assets/Tiled/json/Normal.json") {}

  void Init() {
    tileMap.Init();
  }

  void Draw() {
    tileMap.Draw();
  }
};

int main (int argc, char *argv[]) {
  
  InitWindow(BLOCK * BOARD, BLOCK * BOARD, "Soil thing");
  SetTargetFPS(60);

  Game game;

  game.Init();

  while ( !WindowShouldClose() )
  { 

    BeginDrawing();

    game.Draw();

    ClearBackground(GRUVBOX_DARK0);

    EndDrawing();
    
  }

  CloseWindow();

  return 0;
}
