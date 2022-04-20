#pragma once

#include "classes/gameobject/player/Player.h"
#include <Engine/Gamepad.hpp>
#include <Engine/OGLGame.hpp>
#include <Engine/Sprite.hpp>
#include <classes/gameobject/GameObject.h>
#include <classes/utility/SpriteComponent.h>
#include <classes/utility/Tiles.h>
#include <map>
#include <soloud.h>
#include <soloud_wav.h>

class ASGENetGame : public ASGE::OGLGame
{
 public:
  explicit ASGENetGame(const ASGE::GameSettings& settings);
  ~ASGENetGame() override;

  ASGENetGame(const ASGENetGame&) = delete;
  ASGENetGame& operator=(const ASGENetGame&) = delete;

 private:
  void init();
  void initAudio();
  void initGame();
  void initPlayer();
  void initHospitalMap();

  void keyHandler(ASGE::SharedEventData data);
  void keyHandlerGame(const auto* key);
  void keyHandlerPlayer(const auto* key);

  void clickHandler(ASGE::SharedEventData data);

  void update(const ASGE::GameTime& us) override;
  void updateMenu();
  void updateGame(const ASGE::GameTime& us);
  void updateBaseGame();
  void updateInterrogation();
  void updateHospitalMap();
  void joystickMenuInput(auto joystick);

  void render(const ASGE::GameTime& us) override;
  void renderMenu();
  void renderGame();
  void renderSplitScreen();
  void renderInterrogation();
  void renderHospitalMap();

  void fixedUpdate(const ASGE::GameTime& us) override;

  // GENERAL
  std::string key_callback_id{}; /**< Key Input Callback ID. */
  std::string mouse_callback_id{};
  std::map<int, bool> keymap{};
  std::map<int, ASGE::GamePadData> gamepad_state{};
  std::unique_ptr<ASGE::Sprite> ship{ nullptr };
  ASGE::Point2D velocity{ 0, 0 };

  ASGE::GameSettings game_settings;
  float old_x_pos = 0;
  float old_y_pos = 0;

  // CAMERAS
  ASGE::Camera camera_one{ 960, 1080 };
  ASGE::Camera camera_two{ 960, 1080 };

  // FONT
  const ASGE::Font* game_font = nullptr;
  ASGE::Text camera_one_label{};
  ASGE::Text camera_two_label{};

  // AUDIO
  SoLoud::Soloud audio_engine;
  SoLoud::Wav background_audio;

  // MENU VARIABLES
  enum GeneralState // Control general video game states
  {
    MENU = 1,
    GAME = 2,
  };
  int general_state = GeneralState::MENU;

  // GAME VARIABLES
  enum GameState // Control game states.
  {
    BASE_GAMEPLAY = 0,
    INTERROGATION = 1,
    HOSPITAL_MAP  = 2,
  };
  int game_state = GameState::BASE_GAMEPLAY;
  Tiles tiles;

  bool split_screen = false;
  Player player;

  // ASSISTANT FUNCTIONS
  [maybe_unused] void setupInitSprites(
    std::unique_ptr<ASGE::Sprite>& sprite, const std::string& texture_file_path, float width,
    float height, int16_t z_order, float x_pos, float y_pos, float scale);
  [maybe_unused] void
  setupTextRender(ASGE::Text& text, int16_t z_order, float x_pos, float y_pos, ASGE::Colour colour);
};
