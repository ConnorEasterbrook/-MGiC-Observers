//
// Created by crobi on 26/04/2022.
//

#ifndef ASGEGAME_HOSPITALSTATE_H
#define ASGEGAME_HOSPITALSTATE_H

#include "State.h"
#include "classes/gameobject/player/Player.h"
#include <algorithm>
#include <classes/gameobject/QuantomObject.h>
#include <classes/utility/SpriteComponent.h>
#include <classes/utility/Tiles.h>

class HospitalState : public State
{
 public:
  explicit HospitalState(
    ASGE::Renderer* renderer, std::stack<State*>* gameStates, ASGE::Input* inputs);
  virtual ~HospitalState() override;

  void inputHandler(ASGE::SharedEventData data) override;
  void fixedUpdate(const ASGE::GameTime& us) override;
  void update(const ASGE::GameTime& us) override;
  void render(const ASGE::GameTime& us, ASGE::Renderer* renderer = nullptr) override;
  void removeState() override;
  void init() override;

  void initPlayer();
  void initHospitalMap();
  void updateHospitalMap(const ASGE::GameTime& us);
  Player player;
  Player playerTwo;
  Tiles tiles;
  float p1_old_x_pos = 0;
  float p1_old_y_pos = 0;

  float p2_old_x_pos = 0;
  float p2_old_y_pos = 0;

  float countdown = 180;
  int game_timer  = 0;
  ASGE::Text game_timer_text;
  int score                        = MAX_BONUS_SCORE;
  static const int MAX_BONUS_SCORE = 50040;
  static const int SECONDS_PENALTY = 834;
  ASGE::Text score_text;
  [maybe_unused] void setupTextRender(
    ASGE::Text& text, int16_t z_order, float x_pos, float y_pos, ASGE::Colour colour, float scale);
  void renderHospitalMap();
  void keyHandlerPlayer(const auto* key);
  ASGE::Point2D velocity{ 0, 0 };
  ASGE::Point2D velocityTwo{ 0, 0 };
  void gamepadHandler();

  void initCameras();

  SoLoud::Wav hospital_music;

  std::unique_ptr<QuantomObject> qObject;

 private:
  const ASGE::Font* ingame_font = nullptr;

  // bool initialized = false;
  ASGE::Camera camera{ 1280, 360 };
  ASGE::Camera camera2{ 1280, 360 };
  ASGE::Viewport viewport1;
  ASGE::Viewport viewport2;
};

#endif // ASGEGAME_HOSPITALSTATE_H
