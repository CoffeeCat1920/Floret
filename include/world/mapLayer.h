#pragma once
#include "../../include/nlohmann/json_utils.hpp"

#include <string>
#include <vector>

class MapLayer {

private:

  std::vector<std::vector<int>> tileGrid;
 
  std::string name;

  int id = 0;

  int layerWidth = 0;
  int layerHeight = 0;

  float opacity = 1.0f; 

public:

  MapLayer(const json& layerData);
  
  std::string Name(); 
  int Id();
  int Width(); 
  int Height();

  const std::vector<std::vector<int>>& Grid();

};
