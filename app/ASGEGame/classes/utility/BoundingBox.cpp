#include "BoundingBox.h"

bool BoundingBox::collision(
  float object_xPos, float object_yPos, float object_width, float object_height) const
{
  return this->xPos<object_xPos + object_width&& this->xPos + this->width> object_xPos &&
         this->yPos<object_yPos + object_height&& this->yPos + this->height> object_yPos;
}

[[maybe_unused]] bool BoundingBox::isBetween(float value, float min, float max) const
{
  return (value >= min) && (value <= max);
}

bool BoundingBox::feetCollision(
  float object_xPos, float object_yPos, float object_width, float object_height) const
{
  return this->xPos + this->width * .45F < object_xPos + object_width &&
         this->yPos + this->height > object_yPos && this->xPos + this->width * .55F > object_xPos &&
         this->yPos + this->height - 1 < object_yPos + object_height;
}
bool BoundingBox::leftWallCollision(
  float object_xPos, float object_yPos, float object_width, float object_height) const
{
  return (this->xPos + width / 4 < object_xPos + object_width * .3F &&
          this->xPos + width / 4 > object_xPos && this->yPos + this->height > object_yPos &&
          this->yPos + this->height - 1 < object_yPos + object_height) ||
         (this->xPos + this->width * .75F > object_xPos &&
          this->xPos + this->width * .75F < object_xPos + object_width * .3f &&
          this->yPos + this->height > object_yPos &&
          this->yPos + this->height - 1 < object_yPos + object_height);
}

bool BoundingBox::rightWallCollision(
  float object_xPos, float object_yPos, float object_width, float object_height) const
{
  return (this->xPos + width / 4 > object_xPos + object_width * .75F &&
          this->xPos + width / 4 < object_xPos + object_width &&
          this->yPos + this->height > object_yPos &&
          this->yPos + this->height - 1 < object_yPos + object_height) ||
         (this->xPos + this->width * .75F > object_xPos + object_width * .75F &&
          this->xPos + this->width * .75F < object_xPos + +object_width &&
          this->yPos + this->height > object_yPos &&
          this->yPos + this->height - 1 < object_yPos + object_height);
}
