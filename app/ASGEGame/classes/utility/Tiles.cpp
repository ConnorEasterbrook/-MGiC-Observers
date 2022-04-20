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
#pragma unroll(1)
  for (auto& decorations : collidable_tiles)
  {
    decorations->setGlobalZOrder(1);
    renderer->render(*decorations);
  }

#pragma unroll(1)
  for (auto& collidibles : interactive_tile)
  {
    collidibles->setGlobalZOrder(0);
    renderer->render(*collidibles);
  }

#pragma unroll(1)
  for (auto& walkable : walkable_tile)
  {
    walkable->setGlobalZOrder(-1);
    renderer->render(*walkable);
  }

#pragma unroll(1)
  for (auto& decoration : decoration_tile)
  {
    decoration->setGlobalZOrder(2);
    renderer->render(*decoration);
  }

#pragma unroll(1)
  for (auto& decoration2 : decoration_tile2)
  {
    decoration2->setGlobalZOrder(3);
    renderer->render(*decoration2);
  }

#pragma unroll(1)
  for (auto& decoration2 : void_tile)
  {
    decoration2->setGlobalZOrder(-2);
    renderer->render(*decoration2);
  }
}

[[maybe_unused]] bool Tiles::getWalkable(GameObject& gameObject)
{
  for (auto& walkable : walkable_tile)
  {
    if (gameObject.sprite()
          ->getBoundingBox(gameObject.sprite()->getSprite()->scale(), false)
          .collision(walkable->xPos(), walkable->yPos(), walkable->width(), walkable->height()))
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
          ->getBoundingBox(gameObject.sprite()->getSprite()->scale(), false)
          .collision(
            collidable->xPos(), collidable->yPos(), collidable->width(), collidable->height()))
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
