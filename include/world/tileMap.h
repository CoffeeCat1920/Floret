#pragma once

#include "./tileSet.h"
#include "mapLayer.h"
#include <memory>
#include <string>
#include <vector>

class TileMap {

private:

  std::vector<std::shared_ptr<MapLayer>> layers;

  std::string dataPath;

  TileSet tileSet;

  int mapWidth;
  int mapHeight;

public:

  TileMap(std::string dataPaht);

  void Init();
  void Draw();
};
