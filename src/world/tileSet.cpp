#include "../../include/world/tileSet.h"
#include "../../include/core/settings.h"
#include "../../include/raylib/raylib.h"
#include "../../include/nlohmann/json_utils.hpp"
#include <cstdint>
#include <fstream>
#include <iostream>

TileSet::TileSet() {}
TileSet::~TileSet() {}

int TileSet::GetTileWidth() { return tileWidth; }
int TileSet::GetTileHeight() { return tileHeight; }

void TileSet::Init(std::string dataPath) {

  this->dataPath = dataPath;

  std::ifstream file(dataPath); 
  if (!file.is_open()) {
    std::cerr << "Could not open TileSet.json\n";
    return;
  }

  json tileData;
  file >> tileData;

  name = tileData["name"];

  imageHeight = tileData["imageheight"];
  imageWidth = tileData["imagewidth"];

  tileWidth = tileData["tilewidth"];
  tileHeight = tileData["tileheight"];

  atlasPath = tileData["image"];

  tileCount = tileData["tilecount"];

  tiles.resize(tileCount);

  for (const auto& tile : tileData["tiles"]) {
    if (!tile.contains("id") || !tile.contains("properties")) continue;

    int id = tile["id"];
    std::string tileName;

    for (const auto& prop : tile["properties"]) {
      if (prop["name"] == "Name") {
        tileName = prop["value"];
        break;
      }
    }

    if (id >= 0 && id < tileCount) {
      tiles[id] = std::make_shared<Tile>(tileName);
    }
  }
  
  atlasPath = atlasPath.replace(0, 5, "./assets");
  atlasTexture = LoadTexture(atlasPath.c_str());

  for (int x = 0; x < imageWidth; x += tileWidth) {
    for (int y = 0; y < imageHeight; y += tileHeight) {
      Rectangle rec = Rectangle{(float)x, (float)y, (float)tileWidth, (float)tileHeight};
      texturesRecs.push_back(rec);
    }
  }

  std::cout << "INFO: TILESET [" << atlasPath << "] Tileset loaded successfully" << std::endl; 

}

void TileSet::DrawTile(uint16_t tileId, int x, int y) {
  if (tileId >= tiles.size() || !tiles[tileId]) {
    std::cerr << "Invalid tileId: " << tileId << '\n';
    return;
  }

  float positionX = (x - y) * (BLOCK_X / 2.0f) - (BLOCK_X / 2.0f) + (BLOCK * BOARD/ 2.0f);
  float positionY = (x + y) * (BLOCK_Y / 2.0f) + (BLOCK * BOARD/ 4.0f);

  DrawTextureRec(atlasTexture, texturesRecs[tileId], Vector2{positionX, positionY}, WHITE);
}
