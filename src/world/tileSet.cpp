#include "../../include/world/tileSet.h"
#include "../../include/core/settings.h"
#include "../../include/core/camera.h"
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
    std::cout << "Loaded tile named: " << tileName << "\n";
  }
  
  atlasPath = atlasPath.replace(0, 5, "./assets");
  atlasTexture = LoadTexture(atlasPath.c_str());

  for (int x = 0; x < imageWidth; x += tileWidth) {
    for (int y = 0; y < imageHeight; y += tileHeight) {
      Rectangle rec = Rectangle{(float)x, (float)y, (float)tileWidth, (float)tileHeight};
      texturesRecs.push_back(rec);
    }
  }

  std::cout << "INFO: TILESET [" << atlasPath << "] Tileset loaded successfully" << "\n"; 
}


void TileSet::DrawEmptyTile(float posX, float posY) {
    Vector2 posA = Vector2{posX + (BLOCK_X * 0.5f), posY + (BLOCK_Y * 1.0f)};
    Vector2 posB = Vector2{posX + (BLOCK_X * 1.0f), posY + (BLOCK_Y * 1.5f)};
    Vector2 posC = Vector2{posX + (BLOCK_X * 0.0f), posY + (BLOCK_Y * 1.5f)}; 
    Vector2 posD = Vector2{posX + (BLOCK_X * 0.5f), posY + (BLOCK_Y * 2.0f)};

    DrawLineEx(posA, posB, 2.0f, WHITE);
    DrawLineEx(posC, posD, 2.0f, WHITE);
    DrawLineEx(posA, posC, 2.0f, WHITE);
    DrawLineEx(posB, posD, 2.0f, WHITE);
}

Vector2 TileSet::GetTileWorldPos(int x, int y) {
    float worldX = (x - y) * (BLOCK_X * 0.5f) - (BLOCK_X * 0.5f) + (BLOCK * BOARD * 0.22f);
    float worldY = (x + y) * (BLOCK_Y * 0.5f) + (BLOCK * BOARD * (1.0f / 6.0f));
    return {worldX, worldY};
}

bool TileSet::IsClickedOnRight(uint16_t tileId, int x, int y) {
  Vector2 pos = GetTileWorldPos(x, y);

  Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
  
  Rectangle hitbox = { 
    pos.x + tileWidth * 0.5f - 4, 
    pos.y + 4, 
    (float)tileWidth - 24, 
    (float)tileHeight - 24 
  };
  
  if (CheckCollisionPointRec(mouseWorld, hitbox)) {
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
      return true;
    }
  }

  return false; 
}

bool TileSet::IsClickedOnLeft(uint16_t tileId, int x, int y) {
  Vector2 pos = GetTileWorldPos(x, y);

  Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
  
  Rectangle hitbox = { 
    pos.x + tileWidth * 0.5f - 4, 
    pos.y + 4, 
    (float)tileWidth - 24, 
    (float)tileHeight - 24 
  };

  DrawRectangleRec(hitbox, BLACK);
  
  if (CheckCollisionPointRec(mouseWorld, hitbox)) {
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      return true;
    }
  }

  return false; 
}

// I shouldn't be having all this inside Draw, I should've have the Update, Sorry 
void TileSet::DrawTile(uint16_t tileId, int x, int y) {
  Vector2 pos = GetTileWorldPos(x, y);
  
  if (tileId <= 0) {
    DrawEmptyTile(pos.x, pos.y);
    return;
  }

  Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
  
  Rectangle hitbox = { 
    pos.x + tileWidth * 0.5f - 4, 
    pos.y + 4, 
    (float)tileWidth - 24, 
    (float)tileHeight - 24 
  };
  
  if (CheckCollisionPointRec(mouseWorld, hitbox)) {
    pos.y -= 6.0f;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      std::cout << "Clicked at x:" << pos.x << ", y:" << pos.y << "\n"; 
    }
  }

  DrawTextureRec(atlasTexture, texturesRecs[tileId-1], pos, WHITE);
}
