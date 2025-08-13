#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "./tile.h"
#include "raylib.h"

class TileSet {
private:
  std::string dataPath;
  std::vector<std::shared_ptr<Tile>> tiles;

  std::string atlasPath;
  std::string name;

  int imageWidth = 0;
  int imageHeight = 0;

  int tileWidth = 0;
  int tileHeight = 0;

  int tileCount = 0;

  Texture2D atlasTexture;
  
  std::vector<Rectangle> texturesRecs;

  void DrawEmptyTile(float posX, float posY);
  Vector2 GetTileWorldPos(int x, int y); 
  
public:
  TileSet();
  ~TileSet();

  bool IsClickedOnRight(uint16_t tileId, int x, int y); 
  bool IsClickedOnLeft(uint16_t tileId, int x, int y);

  int GetTileWidth();
  int GetTileHeight();

  void Init(std::string dataPath);
  void Update();
  void DrawTile(uint16_t tileId, int x, int y);
};
