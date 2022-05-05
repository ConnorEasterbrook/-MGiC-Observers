#ifndef ASGEGAME_TILES_H
#define ASGEGAME_TILES_H

#include "../gameobject/GameObject.h"
#include "iostream"
#include <Engine/FileIO.hpp>
#include <Engine/Renderer.hpp>
#include <Engine/Sprite.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>

class Tiles
{
 public:
  Tiles()  = default;
  ~Tiles() = default;

  void initTileInit(ASGE::Renderer* renderer);
  [[maybe_unused]] std::vector<std::unique_ptr<ASGE::Sprite>> getTile(std::string tileset);
  [[maybe_unused]] float getTileScale() const;
  void renderTiles(ASGE::Renderer* renderer);
  [[maybe_unused]] bool getWalkable(GameObject& gameObject);
  [[maybe_unused]] bool getCollidables(GameObject& gameObject);
  [[maybe_unused]] bool getRightTile(GameObject& gameObject);
  [[maybe_unused]] bool getLeftTile(GameObject& gameObject);
  [[maybe_unused]] bool getEndTile(GameObject& gameObject);

  void hospitalMapCreation();

  const int HOSPITAL_DEFAULT_CLOCKS = 1;
  int rendered_clock_count          = 0;
  int hospital_clocks               = HOSPITAL_DEFAULT_CLOCKS;
  bool hospital_furniture[9];

 private:
  void initTileMap(ASGE::Renderer* renderer);
  void initTiles(
    const auto& layer, const auto* tile, int tile_x_pos, int tile_y_pos, ASGE::Renderer* renderer);
  void tileSpriteSetup(const auto* tile, auto& sprite, int tile_x_pos, int tile_y_pos);

  tmx::Map map;

  int tile_size      = 32;
  int tile_scale     = 1;
  int interactive_cc = 0;
  int collidable_cc  = 0;
  int walkable_cc    = 0;

  std::vector<std::unique_ptr<ASGE::Sprite>> collidable_tiles;
  std::vector<std::unique_ptr<ASGE::Sprite>> interactive_tile;
  std::vector<std::unique_ptr<ASGE::Sprite>> walkable_tile;
  std::vector<std::unique_ptr<ASGE::Sprite>> decoration_tile;
  std::vector<std::unique_ptr<ASGE::Sprite>> decoration_tile2;
  std::vector<std::unique_ptr<ASGE::Sprite>> void_tile;
  std::vector<std::unique_ptr<ASGE::Sprite>> quantum_toilet_tile;
  std::vector<std::unique_ptr<ASGE::Sprite>> quantum_plant_tile;
  std::vector<std::unique_ptr<ASGE::Sprite>> quantum_clock_tile_top;
  std::vector<std::unique_ptr<ASGE::Sprite>> quantum_clock_tile_bot;
  std::vector<std::unique_ptr<ASGE::Sprite>> quantum_curtain_tile_decoration;
  std::vector<std::unique_ptr<ASGE::Sprite>> quantum_curtain_tile_collidable;
  std::vector<std::unique_ptr<ASGE::Sprite>> quantum_bin_tile;
  std::vector<std::unique_ptr<ASGE::Sprite>> quantum_freezer_tile;
  std::vector<std::unique_ptr<ASGE::Sprite>> quantum_bed_tile;
  std::vector<std::unique_ptr<ASGE::Sprite>> quantum_computer_screens_tile;
  std::vector<std::unique_ptr<ASGE::Sprite>> quantum_fire_extinguisher_tile;
  std::vector<std::unique_ptr<ASGE::Sprite>> quantum_vending_machine_tile;
  std::vector<std::unique_ptr<ASGE::Sprite>> left_wall_tile;
  std::vector<std::unique_ptr<ASGE::Sprite>> right_wall_tile;
  std::vector<std::unique_ptr<ASGE::Sprite>> end_tile;
  std::vector<std::unique_ptr<ASGE::Sprite>> y2_tile;
  std::vector<std::unique_ptr<ASGE::Sprite>> y3_tile;

  int rng_clocks_q = 0;
  int rng_tile     = 0;
};

#endif // ASGEGAME_TILES_H
