#ifndef NOTMARIOGAME_SPRITECOMPONENT_H
#define NOTMARIOGAME_SPRITECOMPONENT_H

#include "BoundingBox.h"
#include "iostream"
#include "random"
#include "vector"
#include <Engine/Renderer.hpp>
#include <Engine/Sprite.hpp>

class SpriteComponent
{
 public:
  SpriteComponent()  = default;
  ~SpriteComponent() = default;

  void render(ASGE::Renderer* renderer);
  void newSprite(const std::string& texture_file_name, ASGE::Renderer* renderer, int z_order);
  void setSprite(const std::string& texture_file_name);
  void setX(float x);
  void setY(float y);
  float getX();
  float getY();
  float getTrueWidth();
  float getTrueHeight();
  void setBounds(float x, float y);
  void setDimensions(float w, float h, float s);
  [[maybe_unused]] void setAnimationCells(const ASGE::GameTime& us);

  [[nodiscard]] BoundingBox getBoundingBox(float scale, bool topdown) const;
  [[nodiscard]] const std::unique_ptr<ASGE::Sprite>& getSprite() const;

 private:
  std::unique_ptr<ASGE::Sprite> sprite = nullptr;
  float width                          = 16;
  float height                         = 16;
  float scale                          = 3;
  float src_x                          = 0;
  float src_y                          = 0;
  float animation_timer{};
  unsigned int animation_index{};
};

#endif // NOTMARIOGAME_SPRITECOMPONENT_H
