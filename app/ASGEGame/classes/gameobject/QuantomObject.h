//
// Created by crobi on 19/02/2022.
//

#ifndef NOTMARIOGAME_QUANTOMOBJECT_H
#define NOTMARIOGAME_QUANTOMOBJECT_H

#include <Engine/OGLGame.hpp>
#include <Engine/Renderer.hpp>
#include <Engine/Sprite.hpp>
class QuantomObject
{
 public:
  explicit QuantomObject(ASGE::Renderer& gameRenderer, float xPos, float yPos);
  ~QuantomObject();
  [[nodiscard]] ASGE::Sprite* getSprite1() const;
  [[nodiscard]] ASGE::Sprite* getSprite2() const;
  bool initSprites(float xPos, float yPos);
  void render(int viewport);

 private:
  std::unique_ptr<ASGE::Sprite> sprite1;
  std::unique_ptr<ASGE::Sprite> sprite2;

 protected:
  std::unique_ptr<ASGE::Renderer> renderer;
};

#endif // NOTMARIOGAME_QUANTOMOBJECT_H
