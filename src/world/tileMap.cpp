#include "../../include/world/tileMap.h"
#include "../../include/nlohmann/json_utils.hpp"
#include "raylib.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

TileMap::TileMap(std::string dataPath) : 
  dataPath(dataPath) {}
  
void TileMap::Init() {

  tileSet.Init("./assets/Tiled/json/Default.json");

  std::ifstream file(dataPath);
  if (!file.is_open()) {
    std::cerr << "Could not open TileSet.json\n";
    return;
  }

  json mapData;

  file >> mapData;

  mapWidth = mapData["width"];
  mapHeight = mapData["height"];

  for (const auto& layer : mapData["layers"]) {
    layers.push_back(std::make_shared<MapLayer>(layer));
  } 

  std::cout << "INFO: TILEMAP [" << dataPath << "] Tilemap loaded successfully" << std::endl; 

}

void TileMap::Draw() {
  std::shared_ptr<MapLayer> layer = layers[0];
  const std::vector<std::vector<int>> tileGrid = layer->Grid();

  for (int x = 0; x < mapHeight; ++x) {
    for (int y = 0; y < mapWidth; ++y) {
      int tileId = tileGrid[x][y];
      tileSet.DrawTile(tileId, x, y);
      if (tileSet.IsClickedOnRight(tileId, x, y)) {
        layer->ChangeTile(0, x, y); 
      }
      else if (tileSet.IsClickedOnLeft(tileId, x, y)) {
        layer->ChangeTile(1, x, y); 
      }
    }
  }

}
