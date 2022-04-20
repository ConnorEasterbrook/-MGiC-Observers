#include "Player.h"

void Player::setPlayerSpawn(int x_pos, int y_pos)
{
  spawn_xPos = x_pos;
  spawn_yPos = y_pos;
}

void Player::teleportPlayerSpawn()
{
  sprite()->setX(static_cast<float>(spawn_xPos));
  sprite()->setY(static_cast<float>(spawn_yPos));
}

float Player::getPlayerSpeed() const
{
  return player_speed;
}
[[maybe_unused]] void Player::setPlayerSpeed(float playerSpeed)
{
  player_speed = playerSpeed;
}

void Player::playerUpdate(const ASGE::GameTime& us)
{
  playerMovement(us);
}

void Player::gamepadInput(ASGE::Point2D velocity)
{
  player_velocity = velocity;

  if (velocity.x > 1)
  {
    rightMovementKey = true;
    leftMovementKey  = false;
  }
  else if (velocity.x < -1)
  {
    leftMovementKey  = true;
    rightMovementKey = false;
  }
  else
  {
    rightMovementKey = false;
    leftMovementKey  = false;
  }

  if (velocity.y > 1)
  {
    downMovementKey = true;
    upMovementKey   = false;
  }
  else if (velocity.y < -1)
  {
    upMovementKey   = true;
    downMovementKey = false;
  }
  else
  {
    upMovementKey   = false;
    downMovementKey = false;
  }
}

void Player::playerMovement(const ASGE::GameTime& us)
{
  if (rightMovementKey)
  {
    sprite()->setX(sprite()->getX() + ((player_velocity.x / 75) + getPlayerSpeed()));
    sprite()->getSprite()->setFlipFlags(ASGE::Sprite::FLIP_X);
  }
  if (leftMovementKey)
  {
    sprite()->setX(sprite()->getX() - ((-player_velocity.x / 75) + getPlayerSpeed()));
    sprite()->getSprite()->setFlipFlags(ASGE::Sprite::NORMAL);
  }
  if (downMovementKey)
  {
    sprite()->setY(sprite()->getY() + ((player_velocity.y / 75) + getPlayerSpeed()));
  }
  if (upMovementKey)
  {
    sprite()->setY(sprite()->getY() - ((-player_velocity.y / 75) + getPlayerSpeed()));
  }

  animationCheck(us);
}

void Player::animationCheck(const ASGE::GameTime& us)
{
  if (rightMovementKey || leftMovementKey)
  {
    animatePlayer(us, 16);
  }
  else if (upMovementKey)
  {
    animatePlayer(us, 48);
  }
  else if (downMovementKey)
  {
    animatePlayer(us, 0);
  }
}

void Player::animatePlayer(const ASGE::GameTime& us, float y_offset)
{
  std::array<std::array<float, 4>, 4> animation_cells{};
  animation_cells[0] = {
    src_x, src_y + y_offset, sprite()->getSprite()->width(), sprite()->getSprite()->height()
  };
  animation_cells[1] = { src_x - sprite()->getSprite()->width(),
                         src_y + y_offset,
                         sprite()->getSprite()->width(),
                         sprite()->getSprite()->height() };
  animation_cells[2] = {
    src_x, src_y + y_offset, sprite()->getSprite()->width(), sprite()->getSprite()->height()
  };
  animation_cells[3] = { src_x + sprite()->getSprite()->width(),
                         src_y + y_offset,
                         sprite()->getSprite()->width(),
                         sprite()->getSprite()->height() };

  constexpr float ANIMATION_FRAME_RATE = 1.F / 10.F;
  animation_timer += static_cast<float>(us.deltaInSecs());
  if (animation_timer > ANIMATION_FRAME_RATE)
  {
    if (animation_tick < 3)
    {
      animation_tick++;
    }
    else
    {
      animation_tick = 0;
    }
    animation_timer = 0.0F;
  }

  sprite()->getSprite()->srcRect()[0] = animation_cells[animation_tick][0];
  sprite()->getSprite()->srcRect()[1] = animation_cells[animation_tick][1];
  sprite()->getSprite()->srcRect()[2] = animation_cells[animation_tick][2];
  sprite()->getSprite()->srcRect()[3] = animation_cells[animation_tick][3];
}

void Player::selectSprite()
{
  std::random_device dev_spritesheet;
  std::mt19937 rng_spritesheet(dev_spritesheet());
  std::uniform_int_distribution<std::mt19937::result_type> dist_spritesheet(1, 3);
  character_spritesheet = static_cast<int>(dist_spritesheet(rng_spritesheet));

  selectSpritesheet();

  std::random_device dev_character;
  std::mt19937 rng_character(dev_character());
  if (character_spritesheet == 1)
  {
    selection_range = 9;
    std::uniform_int_distribution<std::mt19937::result_type> dist_characters(0, selection_range);
    character_selection = static_cast<float>(round(dist_characters(rng_character)));
  }
  else
  {
    selection_range = 7;
    std::uniform_int_distribution<std::mt19937::result_type> dist_characters(0, selection_range);
    character_selection = static_cast<float>(round(dist_characters(rng_character)));
  }

  selectCharacter();
}

void Player::selectSpritesheet()
{
  switch (character_spritesheet)
  {
    case 1:
      sprite()->setSprite("data/images/characters/01-generic.png");
      break;

    case 2:
      sprite()->setSprite("data/images/characters/05-devout.png");
      break;

    default:
      sprite()->setSprite("data/images/characters/06-conjurer.png");
      break;
  }

  sprite()->setDimensions(16, 16, 3);
}

void Player::selectCharacter()
{
  if (character_selection < static_cast<float>(selection_range / 2))
  {
    src_x = sprite()->getSprite()->width() + (sprite_distance * character_selection);
    src_y = 0;
    sprite()->setBounds(
      sprite()->getSprite()->width() + (sprite_distance * character_selection), src_y);
  }
  else
  {
    std::random_device dev_rng;
    std::mt19937 rng(dev_rng());
    float sprite_selection = 0;
    if (character_spritesheet == 1)
    {
      std::uniform_int_distribution<std::mt19937::result_type> dist_rng(0, 4);
      sprite_selection = static_cast<float>(dist_rng(rng));
    }
    else
    {
      std::uniform_int_distribution<std::mt19937::result_type> dist_rng(0, 3);
      sprite_selection = static_cast<float>(dist_rng(rng));
    }

    src_x = sprite()->getSprite()->width() + (sprite_distance * sprite_selection);
    src_y = 64;
    sprite()->setBounds(
      sprite()->getSprite()->width() + (sprite_distance * sprite_selection), src_y);
  }
}

// void Player::playerCollisions(
//  std::vector<std::unique_ptr<ASGE::Sprite>> collidables, float tile_size)
//{
//#pragma unroll(1)
//  for (auto& collision_tiles : collidables)
//  {
//    collision_tiles->width(tile_size);
//    collision_tiles->height(tile_size);
//
//    if (sprite()
//          ->getBoundingBox(sprite()->getSprite()->scale())
//          .collision(
//            collision_tiles->xPos(),
//            collision_tiles->yPos(),
//            collision_tiles->width(),
//            collision_tiles->height()))
//    {
//      if
//    }
//  }
//}
