#include "SpriteComponent.h"

void SpriteComponent::render(ASGE::Renderer* renderer)
{
  if (sprite)
  {
    renderer->render(*sprite);
  }
}

void SpriteComponent::newSprite(
  const std::string& texture_file_name, ASGE::Renderer* renderer, int z_order)
{
  sprite = renderer->createUniqueSprite();
  sprite->setGlobalZOrder(static_cast<int16_t>(z_order));
  sprite->loadTexture(texture_file_name);
}

void SpriteComponent::setSprite(const std::string& texture_file_name)
{
  sprite->loadTexture(texture_file_name);
}

void SpriteComponent::setX(float x)
{
  sprite->xPos(x);
}

void SpriteComponent::setY(float y)
{
  sprite->yPos(y);
}

float SpriteComponent::getX()
{
  return sprite->xPos();
}

float SpriteComponent::getY()
{
  return sprite->yPos();
}

float SpriteComponent::getTrueWidth()
{
  return height * scale;
}

float SpriteComponent::getTrueHeight()
{
  return width * scale;
}

void SpriteComponent::setBounds(float posX, float posY)
{
  src_x = posX;
  src_y = posY;

  getSprite()->srcRect()[0] = posX;
  getSprite()->srcRect()[1] = posY;
  getSprite()->srcRect()[2] = width;
  getSprite()->srcRect()[3] = height;
}

void SpriteComponent::setDimensions(float w, float h, float s)
{
  width  = w;
  height = h;
  scale  = s;

  getSprite()->width(w);
  getSprite()->height(h);
  getSprite()->scale(s);

  getSprite()->setMagFilter(ASGE::Texture2D::MagFilter::NEAREST);
}

BoundingBox SpriteComponent::getBoundingBox(float sprite_scale, bool topdown) const
{
  BoundingBox bounding_box;
  if (!topdown)
  {
    bounding_box.xPos   = sprite->xPos();
    bounding_box.yPos   = sprite->yPos();
    bounding_box.width  = sprite->width() * sprite_scale;
    bounding_box.height = sprite->height() * sprite_scale;
  }
  else
  {
    bounding_box.xPos   = sprite->xPos();
    bounding_box.yPos   = sprite->yPos() + (sprite->height() * sprite_scale);
    bounding_box.width  = sprite->width() * sprite_scale;
    bounding_box.height = sprite->height() - (sprite->height() / sprite_scale);
  }

  return bounding_box;
}

const std::unique_ptr<ASGE::Sprite>& SpriteComponent::getSprite() const
{
  return sprite;
}

[[maybe_unused]] void SpriteComponent::setAnimationCells(const ASGE::GameTime& us)
{
  std::array<std::array<float, 4>, 4> animation_cells{};
  animation_cells[0] = { src_x, src_y, getSprite()->width(), getSprite()->height() };
  animation_cells[1] = { src_x + width, src_y, getSprite()->width(), getSprite()->height() };
  animation_cells[2] = { src_x + (width * 2), src_y, getSprite()->width(), getSprite()->height() };
  animation_cells[3] = { src_x + (width * 3), src_y, getSprite()->width(), getSprite()->height() };

  constexpr float ANIMATION_FRAME_RATE = 1.F / 10.F;

  animation_timer += static_cast<float>(us.deltaInSecs());
  if (animation_timer > ANIMATION_FRAME_RATE)
  {
    animation_index = 1 - animation_index;
    animation_timer = 0.0F;
  }

  getSprite()->srcRect()[0] = animation_cells[animation_index][0];
  getSprite()->srcRect()[1] = animation_cells[animation_index][1];
  getSprite()->srcRect()[2] = animation_cells[animation_index][2];
  getSprite()->srcRect()[3] = animation_cells[animation_index][3];
}
