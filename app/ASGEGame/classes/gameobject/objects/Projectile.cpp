#include "Projectile.hpp"

[[maybe_unused]] void Projectile::setProjectileDirection(int x_pos, int y_pos)
{
  projectileDirection.x = static_cast<float>(x_pos);
  projectileDirection.y = static_cast<float>(y_pos);
}

void Projectile::setProjectileSpeed(float speed)
{
  projectileSpeed = speed;
}

void Projectile::setProjectilePosition(int x_pos, int y_pos)
{
  spawn_xPos = x_pos;
  spawn_yPos = y_pos;
}

void Projectile::projectileUpdate(const ASGE::GameTime& us)
{
  projectileMovement(us);
}

void Projectile::projectileMovement(const ASGE::GameTime& us)
{
  sprite()->setX(sprite()->getX() + ((projectileDirection.x) + getProjectileSpeed()));

  if (
    sprite()->getX() >= static_cast<float>(spawn_xPos + 100) ||
    sprite()->getX() <= static_cast<float>(spawn_xPos))
  {
    projectileDirection.x = -projectileDirection.x;
    projectileSpeed       = -projectileSpeed;
  }
}
float Projectile::getProjectileSpeed() const
{
  return projectileSpeed;
}

void Projectile::setProjectileSpawn()
{
  sprite()->setX(static_cast<float>(spawn_xPos));
  sprite()->setY(static_cast<float>(spawn_yPos));
}

void Projectile::projectileGoRight()
{
  sprite()->setX(sprite()->getX() + ((projectileDirection.x / 25) + getProjectileSpeed()));
}

void Projectile::projectileGoLeft()
{
  sprite()->setX(sprite()->getX() - ((projectileDirection.x / 25) + getProjectileSpeed()));
}
