#include "../../include/world/tile.h"
#include <string>

Tile::Tile (std::string name) : name(name) {}

std::string Tile::Name() {
  return name;
}
