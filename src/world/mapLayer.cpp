#include "../../include/world/mapLayer.h"
#include <vector>

MapLayer::MapLayer(const json& layerData) {

  id = layerData["id"];
  name = layerData["name"];

  layerWidth = layerData["width"];
  layerHeight = layerData["height"];

  const auto& data = layerData["data"];

  tileGrid.resize(layerHeight, std::vector<int>(layerWidth));

  for (int x = 0; x < layerWidth; ++x) {
    for (int y = 0; y < layerHeight; ++y) {
      tileGrid[x][y] = data[y * layerWidth + x];
    }
  }

}

std::string MapLayer::Name() { return name; }
int MapLayer::Id() { return id; }
int MapLayer::Width() { return layerWidth; } 
int MapLayer::Height() { return layerHeight; }

const std::vector<std::vector<int>>& MapLayer::Grid() { return tileGrid; }
