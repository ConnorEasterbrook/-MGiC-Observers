//
// Created by crobi on 19/02/2022.
//

#include "QuantomObject.h"
#include <Engine/Logger.hpp>

QuantomObject::QuantomObject(ASGE::Renderer& gameRenderer, float xPos, float yPos) :
  renderer(&gameRenderer)
{
  initSprites(xPos, yPos);
}
ASGE::Sprite* QuantomObject::getSprite1() const
{
  return sprite1.get();
}
ASGE::Sprite* QuantomObject::getSprite2() const
{
  return sprite2.get();
}
bool QuantomObject::initSprites(float xPos, float yPos)
{
  sprite1 = renderer->createUniqueSprite();
  if (!sprite1->loadTexture("/data/images/coin1.png"))
  {
    Logging::WARN("Sprite1 Failed To Load");
    return false;
  }

  sprite2 = renderer->createUniqueSprite();
  if (!sprite2->loadTexture("/data/images/coin2.png"))
  {
    Logging::WARN("Sprite2 Failed To Load");
    return false;
  }

  sprite1->width(16);
  sprite1->height(16);
  sprite1->scale(3);
  sprite1->xPos(xPos);
  sprite1->yPos(yPos);
  sprite1->setGlobalZOrder(31000);
  sprite1->setMagFilter(ASGE::Texture2D::MagFilter::NEAREST);
  sprite2->width(16);
  sprite2->height(16);
  sprite2->scale(3);
  sprite2->xPos(xPos);
  sprite2->yPos(yPos);
  sprite2->setGlobalZOrder(31000);
  sprite2->setMagFilter(ASGE::Texture2D::MagFilter::NEAREST);
  return true;
}
void QuantomObject::render(int viewport)
{
  if (viewport == 1)
  {
    renderer->render(*sprite1);
  }
  if (viewport == 2)
  {
    renderer->render(*sprite2);
  }
}
QuantomObject::~QuantomObject() = default;
