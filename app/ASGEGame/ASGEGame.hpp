#pragma once
#include <classes/States/MainGameState.h>
#include <classes/gameobject/objects/Projectile.hpp>
/*#include <Engine/Gamepad.hpp>
#include <Engine/OGLGame.hpp>
#include <Engine/Sprite.hpp>

#include <map>
#include <soloud.h>
#include <soloud_wav.h>*/

class ASGENetGame : public ASGE::OGLGame
{
 public:
  explicit ASGENetGame(const ASGE::GameSettings& settings);
  ~ASGENetGame() override;

  ASGENetGame(const ASGENetGame&) = delete;
  ASGENetGame& operator=(const ASGENetGame&) = delete;

  void initProjectiles();

 private:
  std::stack<State*> gameStates;

  //
  //  void init();
  void keyHandler(ASGE::SharedEventData data);
  void update(const ASGE::GameTime& us) override;
  void render(const ASGE::GameTime& us) override;
  void fixedUpdate(const ASGE::GameTime& us) override;

  //  void updateMenu();
  //  void updateGame();

  //  void renderMenu();
  //  void renderGame();

  // GENERAL
  std::string key_callback_id{}; /**< Key Input Callback ID. */
                                 //  std::map<int, bool> keymap{};
                                 //  std::map<int, ASGE::GamePadData> gamepad_state{};
                                 //  std::unique_ptr<ASGE::Sprite> ship{ nullptr };
                                 //  ASGE::Point2D velocity{ 0, 0 };
                                 //
                                 //  // CAMERAS
                                 //  ASGE::Camera camera_one{ 960, 1080 };
                                 //  ASGE::Camera camera_two{ 960, 1080 };
                                 //
                                 //  // FONT
  const ASGE::Font* game_font = nullptr;
  //  ASGE::Text camera_one_label{};
  //  ASGE::Text camera_two_label{};

  Projectile projectile;

  // ASSISTANT FUNCTIONS
  //  [maybe_unused] void setupInitSprites(
  //    std::unique_ptr<ASGE::Sprite>& sprite, const std::string& texture_file_path, float width,
  //    float height, int16_t z_order, float x_pos, float y_pos, float scale);
  //  [maybe_unused] void
  //  setupTextRender(ASGE::Text& text, int16_t z_order, float x_pos, float y_pos, ASGE::Colour
  //  colour);
};
