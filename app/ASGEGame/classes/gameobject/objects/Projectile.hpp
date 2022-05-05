
#ifndef ASGEGAME_PROJECTILE_HPP
#define ASGEGAME_PROJECTILE_HPP

#include "classes/gameobject/GameObject.h"
#include <Engine/InputEvents.hpp>
#include <Engine/Sprite.hpp>
#include <vector>

class Projectile : public GameObject
{
 public:
  Projectile()           = default;
  ~Projectile() override = default;

  [[maybe_unused]] void setProjectileDirection(int x_pos, int y_pos);
  [[maybe_unused]] void setProjectilePosition(int x_pos, int y_pos);
  [[maybe_unused]] void setProjectileSpeed(float speed);
  [[maybe_unused]] float getProjectileSpeed() const;
  void projectileUpdate(const ASGE::GameTime& us);
  void setProjectileSpawn();
  void projectileGoRight();
  void projectileGoLeft();

 private:
  void projectileMovement(const ASGE::GameTime& us);

  [[maybe_unused]] int spawn_xPos = 0;
  [[maybe_unused]] int spawn_yPos = 0;

  Vector2 projectileDirection = { 0, 0 };

  [[maybe_unused]] float projectileSpeed  = 0;
  [[maybe_unused]] float projectileDamage = 0;

  [[maybe_unused]] bool movingRight = false;
  [[maybe_unused]] bool movingLeft  = false;
  [[maybe_unused]] bool movingUp    = false;
  [[maybe_unused]] bool movingDown  = false;

  enum Direction
  {
    RIGHT,
    LEFT,
    UP,
    DOWN
  };
  [[maybe_unused]] Direction projectileDirection1 = RIGHT;
};

#endif // ASGEGAME_PROJECTILE_HPP
