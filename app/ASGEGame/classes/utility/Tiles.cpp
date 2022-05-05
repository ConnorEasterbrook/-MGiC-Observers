#include "Tiles.h"

void Tiles::initTileInit(ASGE::Renderer* renderer)
{
  ASGE::FILEIO::File tile_map;
  if (tile_map.open("data/map/hospital_map.tmx"))
  {
    ASGE::FILEIO::IOBuffer buffer = tile_map.read();
    std::string file_string(buffer.as_char(), buffer.length);

    map.loadFromString(file_string, ".");

    initTileMap(renderer);
  }

  std::cout << walkable_cc << " walkable blocks." << std::endl;
  std::cout << collidable_cc << " collidible blocks." << std::endl;
  std::cout << interactive_cc << " decoration blocks." << std::endl;
}

void Tiles::initTileMap(ASGE::Renderer* renderer)
{
  for (const auto& layer : map.getLayers())
  {
    if (layer->getType() == tmx::Layer::Type::Tile)
    {
      auto tile_layer = layer->getLayerAs<tmx::TileLayer>();
      int tile_y_pos  = 0;

      for (unsigned int row = 0; row < layer->getSize().y; row++)
      {
        int tile_x_pos = 0;

#pragma unroll(3)
        for (unsigned int col = 0; col < layer->getSize().x; col++)
        {
          auto tile_info = tile_layer.getTiles()[row * tile_layer.getSize().x + col];

          for (const auto& tileset_id : map.getTilesets())
          {
            const auto* tile = tileset_id.getTile(tile_info.ID);

            initTiles(layer, tile, tile_x_pos, tile_y_pos, renderer);
          }

          tile_x_pos += tile_size * tile_scale;
        }
        tile_y_pos += tile_size * tile_scale;
      }
    }
  }
}

void Tiles::initTiles(
  const auto& layer, const auto* tile, int tile_x_pos, int tile_y_pos, ASGE::Renderer* renderer)
{
  if (tile != nullptr)
  {
    if (layer->getName() == "Walkable" || layer->getName() == "Quantum")
    {
      walkable_cc++;

      auto& walk_tile = walkable_tile.emplace_back(renderer->createUniqueSprite());
      walk_tile->loadTexture(tile->imagePath);

      if (walk_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, walk_tile, tile_x_pos, tile_y_pos);
      }
    }
    else if (layer->getName() == "Interactive")
    {
      interactive_cc++;

      auto& collide_tile = interactive_tile.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);

      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }
    else if (layer->getName() == "Decoration")
    {
      collidable_cc++;

      auto& collide_tile = decoration_tile.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);

      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }
    else if (layer->getName() == "Decoration2")
    {
      collidable_cc++;

      auto& collide_tile = decoration_tile2.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);

      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }
    else if (layer->getName() == "void")
    {
      collidable_cc++;

      auto& collide_tile = void_tile.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);

      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }

    else if (layer->getName() == "QuantumToilet")
    {
      collidable_cc++;

      auto& collide_tile = quantum_toilet_tile.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);

      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }

    else if (layer->getName() == "QuantumPlant")
    {
      collidable_cc++;

      auto& collide_tile = quantum_plant_tile.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);

      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }
    else if (layer->getName() == "QuantumClocksT")
    {
      interactive_cc++;

      auto& collide_tile = quantum_clock_tile_top.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);

      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }

    else if (layer->getName() == "QuantumClocksB")
    {
      interactive_cc++;

      auto& collide_tile = quantum_clock_tile_bot.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);
      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }

    else if (layer->getName() == "QuantumCurtainCollidable")
    {
      collidable_cc++;

      auto& collide_tile =
        quantum_curtain_tile_collidable.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);

      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }

    else if (layer->getName() == "QuantumCurtainDecoration")
    {
      collidable_cc++;

      auto& collide_tile =
        quantum_curtain_tile_decoration.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);

      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }
    else if (layer->getName() == "QuantumBin")
    {
      interactive_cc++;

      auto& collide_tile = quantum_bin_tile.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);

      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }

    else if (layer->getName() == "QuantumFreezer")
    {
      interactive_cc++;

      auto& collide_tile = quantum_freezer_tile.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);
      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }
    else if (layer->getName() == "QuantumBed")
    {
      interactive_cc++;

      auto& collide_tile = quantum_bed_tile.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);
      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }
    else if (layer->getName() == "QuantumComputerScreens")
    {
      interactive_cc++;

      auto& collide_tile =
        quantum_computer_screens_tile.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);
      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }
    else if (layer->getName() == "QuantumFireExtinguisher")
    {
      interactive_cc++;

      auto& collide_tile =
        quantum_fire_extinguisher_tile.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);
      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }
    else if (layer->getName() == "QuantumVendingMachine")
    {
      interactive_cc++;

      auto& collide_tile =
        quantum_vending_machine_tile.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);
      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }

    else if (layer->getName() == "RightWall")
    {
      collidable_cc++;

      auto& collide_tile = right_wall_tile.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);
      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }

    else if (layer->getName() == "LeftWall")
    {
      collidable_cc++;

      auto& collide_tile = left_wall_tile.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);
      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }

    else if (layer->getName() == "End")
    {
      collidable_cc++;

      auto& collide_tile = end_tile.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);
      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }

    else if (layer->getName() == "Y2")
    {
      walkable_cc++;

      auto& collide_tile = y2_tile.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);
      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }

    else if (layer->getName() == "Y3")
    {
      walkable_cc++;

      auto& collide_tile = y3_tile.emplace_back(renderer->createUniqueSprite());
      collide_tile->loadTexture(tile->imagePath);
      if (collide_tile->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, collide_tile, tile_x_pos, tile_y_pos);
      }
    }
    else
    {
      collidable_cc++;

      auto& dec_sprite = collidable_tiles.emplace_back(renderer->createUniqueSprite());
      dec_sprite->loadTexture(tile->imagePath);

      if (dec_sprite->loadTexture(tile->imagePath))
      {
        tileSpriteSetup(tile, dec_sprite, tile_x_pos, tile_y_pos);
      }
    }
  }
}

void Tiles::tileSpriteSetup(const auto* tile, auto& sprite, int tile_x_pos, int tile_y_pos)
{
  sprite->srcRect()[0] = static_cast<float>(tile->imagePosition.x);
  sprite->srcRect()[1] = static_cast<float>(tile->imagePosition.y);
  sprite->srcRect()[2] = static_cast<float>(tile->imageSize.x);
  sprite->srcRect()[3] = static_cast<float>(tile->imageSize.y);

  sprite->width(static_cast<float>(tile->imageSize.x));
  sprite->height(static_cast<float>(tile->imageSize.y));
  sprite->scale(static_cast<float>(tile_scale));

  sprite->setMagFilter(ASGE::Texture2D::MagFilter::NEAREST);

  sprite->xPos(static_cast<float>(tile_x_pos));
  sprite->yPos(static_cast<float>(tile_y_pos));
}

void Tiles::renderTiles(ASGE::Renderer* renderer)
{
  rendered_clock_count = 0;
#pragma unroll(1)
  for (auto& decorations : collidable_tiles)
  {
    decorations->setGlobalZOrder(static_cast<int16_t>(1 + (decorations->yPos() * 10)));
    renderer->render(*decorations);
  }

#pragma unroll(1)
  for (auto& collidibles : interactive_tile)
  {
    collidibles->setGlobalZOrder(static_cast<int16_t>(0 + (collidibles->yPos() * 10)));
    renderer->render(*collidibles);
  }

#pragma unroll(1)
  for (auto& walkable : walkable_tile)
  {
    walkable->setGlobalZOrder(static_cast<int16_t>(-1 + (walkable->yPos() * 10)));
    renderer->render(*walkable);
  }

#pragma unroll(1)
  for (auto& decoration : decoration_tile)
  {
    decoration->setGlobalZOrder(static_cast<int16_t>(2 + (decoration->yPos() * 10)));
    renderer->render(*decoration);
  }

#pragma unroll(1)
  for (auto& decoration2 : decoration_tile2)
  {
    decoration2->setGlobalZOrder(static_cast<int16_t>(3 + (decoration2->yPos() * 10)));
    renderer->render(*decoration2);
  }

#pragma unroll(1)
  for (auto& vt : void_tile)
  {
    vt->setGlobalZOrder(static_cast<int16_t>(-2 + (vt->yPos() * 10)));
    renderer->render(*vt);
  }

#pragma unroll(1)
  for (auto& q_toilet : quantum_toilet_tile)
  {
    if (hospital_furniture[0])
    {
      q_toilet->setGlobalZOrder(static_cast<int16_t>(4 + (q_toilet->yPos() * 10)));
      renderer->render(*q_toilet);
    }
  }

#pragma unroll(1)
  for (auto& q_plant : quantum_plant_tile)
  {
    if (hospital_furniture[1])
    {
      q_plant->setGlobalZOrder(static_cast<int16_t>(5 + (q_plant->yPos() * 10)));
      renderer->render(*q_plant);
    }
  }

#pragma unroll(1)
  for (auto& q_curtain_d : quantum_curtain_tile_decoration)
  {
    if (hospital_furniture[2])
    {
      q_curtain_d->setGlobalZOrder(static_cast<int16_t>(2 + (q_curtain_d->yPos() * 10)));
      renderer->render(*q_curtain_d);
    }
  }

#pragma unroll(1)
  for (auto& q_curtain_c : quantum_curtain_tile_collidable)
  {
    if (hospital_furniture[2])
    {
      q_curtain_c->setGlobalZOrder(static_cast<int16_t>(1 + (q_curtain_c->yPos() * 10)));
      renderer->render(*q_curtain_c);
    }
  }

#pragma unroll(1)
  for (auto& q_freezer : quantum_freezer_tile)
  {
    if (hospital_furniture[3])
    {
      q_freezer->setGlobalZOrder(static_cast<int16_t>(6 + (q_freezer->yPos() * 10)));
      renderer->render(*q_freezer);
    }
  }

#pragma unroll(1)
  for (auto& q_bin : quantum_bin_tile)
  {
    if (hospital_furniture[4])
    {
      q_bin->setGlobalZOrder(static_cast<int16_t>(6 + (q_bin->yPos() * 10)));
      renderer->render(*q_bin);
    }
  }

#pragma unroll(1)
  for (auto& q_bed : quantum_bed_tile)
  {
    if (hospital_furniture[5])
    {
      q_bed->setGlobalZOrder(static_cast<int16_t>(1 + (q_bed->yPos() * 10)));
      renderer->render(*q_bed);
    }
  }
#pragma unroll(1)
  for (auto& q_cs : quantum_computer_screens_tile)
  {
    if (hospital_furniture[6])
    {
      q_cs->setGlobalZOrder(static_cast<int16_t>(6 + (q_cs->yPos() * 10)));
      renderer->render(*q_cs);
    }
  }

#pragma unroll(1)
  for (auto& q_fe : quantum_fire_extinguisher_tile)
  {
    if (hospital_furniture[7])
    {
      q_fe->setGlobalZOrder(static_cast<int16_t>(2 + (q_fe->yPos() * 10)));
      renderer->render(*q_fe);
    }
  }

#pragma unroll(1)
  for (auto& q_vm : quantum_vending_machine_tile)
  {
    if (hospital_furniture[8])
    {
      q_vm->setGlobalZOrder(static_cast<int16_t>(6 + (q_vm->yPos() * 10)));
      renderer->render(*q_vm);
    }
  }

#pragma unroll(1)
  for (auto& q_clock : quantum_clock_tile_top)
  {
    if (rendered_clock_count < rng_clocks_q)
    {
      q_clock->setGlobalZOrder(static_cast<int16_t>(7 + (q_clock->yPos() * 10)));
      renderer->render(*q_clock);
      rendered_clock_count++;
    }
  }
  rendered_clock_count = 0;

#pragma unroll(1)
  for (auto& q_clock : quantum_clock_tile_bot)
  {
    if (rendered_clock_count < rng_clocks_q)
    {
      q_clock->setGlobalZOrder(static_cast<int16_t>(7 + (q_clock->yPos() * 10)));
      renderer->render(*q_clock);
      rendered_clock_count++;
    }
  }
  rendered_clock_count = 0;

#pragma unroll(1)
  for (auto& lwt : left_wall_tile)
  {
    lwt->setGlobalZOrder(static_cast<int16_t>(7 + (lwt->yPos() * 10)));
    renderer->render(*lwt);
  }
#pragma unroll(1)
  for (auto& rwt : right_wall_tile)
  {
    rwt->setGlobalZOrder(static_cast<int16_t>(6 + (rwt->yPos() * 10)));
    renderer->render(*rwt);
  }
#pragma unroll(1)
  for (auto& et : end_tile)
  {
    et->setGlobalZOrder(static_cast<int16_t>(6 + (et->yPos() * 10)));
    renderer->render(*et);
  }

#pragma unroll(1)
  for (auto& y2 : y2_tile)
  {
    y2->setGlobalZOrder(static_cast<int16_t>(0 + (((y2->height() * 2) + y2->yPos()) * 10)));
    renderer->render(*y2);
  }

#pragma unroll(1)
  for (auto& y3 : y3_tile)
  {
    y3->setGlobalZOrder(static_cast<int16_t>(6 + (((y3->height() * 3) + y3->yPos()) * 10)));
    renderer->render(*y3);
  }
}

[[maybe_unused]] bool Tiles::getWalkable(GameObject& gameObject)
{
  for (auto& walkable : walkable_tile)
  {
    if (gameObject.sprite()
          ->getBoundingBox(gameObject.sprite()->getSprite()->scale())
          .feetCollision(walkable->xPos(), walkable->yPos(), walkable->width(), walkable->height()))
    {
      return true;
    }
  }

  return false;
}

[[maybe_unused]] bool Tiles::getCollidables(GameObject& gameObject)
{
  for (auto& collidable : void_tile)
  {
    if (gameObject.sprite()
          ->getBoundingBox(gameObject.sprite()->getSprite()->scale())
          .feetCollision(
            collidable->xPos(), collidable->yPos(), collidable->width(), collidable->height()))
    {
      return true;
    }
  }
  return false;
}

[[maybe_unused]] bool Tiles::getRightTile(GameObject& gameObject)
{
  for (auto& right : right_wall_tile)
  {
    if (gameObject.sprite()
          ->getBoundingBox(gameObject.sprite()->getSprite()->scale())
          .rightWallCollision(right->xPos(), right->yPos(), right->width(), right->height()))
    {
      return true;
    }
  }

  return false;
}
[[maybe_unused]] bool Tiles::getLeftTile(GameObject& gameObject)
{
  for (auto& left : left_wall_tile)
  {
    if (gameObject.sprite()
          ->getBoundingBox(gameObject.sprite()->getSprite()->scale())
          .leftWallCollision(left->xPos(), left->yPos(), left->width(), left->height()))
    {
      return true;
    }
  }

  return false;
}
[[maybe_unused]] bool Tiles::getEndTile(GameObject& gameObject)
{
  for (auto& end : end_tile)
  {
    if (gameObject.sprite()
          ->getBoundingBox(gameObject.sprite()->getSprite()->scale())
          .collision(end->xPos(), end->yPos(), end->width(), end->height()))
    {
      return true;
    }
  }

  return false;
}

[[maybe_unused]] float Tiles::getTileScale() const
{
  return static_cast<float>(tile_size * tile_scale);
}

// std::vector<std::unique_ptr<ASGE::Sprite>> Tiles::getTile(std::string tileset)
//{
//  if (tileset == "collidable")
//  {
//    return collidable_tiles;
//  }
//}

void Tiles::hospitalMapCreation()
{
  rng_clocks_q    = 0;
  hospital_clocks = 1;

  std::random_device rng_device;
  std::mt19937 rng_mt(rng_device());
  std::uniform_int_distribution<std::mt19937::result_type> rng_dist(1, 9);
  rng_clocks_q = static_cast<int>(rng_dist(rng_mt));

  hospital_clocks = hospital_clocks + rng_clocks_q;
  std::cout << hospital_clocks << " clocks." << std::endl;

  for (int i = 0; i < 9; ++i)
  {
    std::random_device rng_device_2;
    std::mt19937 rng_mt_2(rng_device_2());
    std::uniform_int_distribution<std::mt19937::result_type> rng_dist_2(1, 2);
    rng_tile = static_cast<int>(rng_dist_2(rng_mt_2));

    rng_tile == 2 ? hospital_furniture[i] = true : hospital_furniture[i] = false;
  }

  std::cout << hospital_furniture[0] << " toilet" << std::endl;
  std::cout << hospital_furniture[1] << " bed plant" << std::endl;
}
