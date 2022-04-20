#ifndef ASGEGAME_PLAYER_H
#define ASGEGAME_PLAYER_H

#include "classes/gameobject/GameObject.h"
#include <Engine/InputEvents.hpp>
#include <Engine/Sprite.hpp>
#include <vector>

class Player : public GameObject
{
 public:
  Player()           = default;
  ~Player() override = default;

  [[maybe_unused]] void setPlayerSpawn(int x_pos, int y_pos);
  [[maybe_unused]] void teleportPlayerSpawn();
  [[maybe_unused]] [[nodiscard]] float getPlayerSpeed() const;
  [[maybe_unused]] void setPlayerSpeed(float playerSpeed);
  [[maybe_unused]] void playerUpdate(const ASGE::GameTime& us);
  void playerCollisions(std::vector<std::unique_ptr<ASGE::Sprite>> collidables, float tile_size);
  void gamepadInput(ASGE::Point2D velocity);

  void selectSprite();

  // PLAYER MOVEMENT
  bool leftMovementKey  = false;
  bool upMovementKey    = false;
  bool downMovementKey  = false;
  bool rightMovementKey = false;

 private:
  void playerMovement(const ASGE::GameTime& us);
  void animationCheck(const ASGE::GameTime& us);
  void animatePlayer(const ASGE::GameTime& us, float y_offset);

  void selectSpritesheet();
  void selectCharacter();

  int spawn_xPos     = 0;
  int spawn_yPos     = 0;
  float player_speed = 1;

  unsigned int selection_range = 8;
  int character_spritesheet    = 0;
  float character_selection    = 0;
  float sprite_distance        = 48;

  float animation_timer{};
  unsigned int animation_tick{};
  float src_x = 0;
  float src_y = 0;

  ASGE::GameSettings game_settings;
  ASGE::Point2D player_velocity{ 0, 0 };
};

#endif // ASGEGAME_PLAYER_H
