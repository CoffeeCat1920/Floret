#pragma once

#include "../raylib/raylib.h"
#include <cstdint>
#include <string>

class Tile {
  
private:
  std::string name;
  
public:

  Tile(std::string name);

  std::string Name();

};
