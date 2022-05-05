//
// Created by crobi on 26/04/2022.
//

#ifndef ASGEGAME_TITLESTATE_H
#define ASGEGAME_TITLESTATE_H

#include "State.h"
#include "classes/gameobject/Buttons.hpp"
#include "classes/utility/Interpolation.h"

class TitleState : public State
{
 public:
  TitleState(ASGE::Renderer* renderer, std::stack<State*>* gameStates, ASGE::Input* inputs);
  virtual ~TitleState() override;

  void inputHandler(ASGE::SharedEventData data) override;
  void fixedUpdate(const ASGE::GameTime& us) override;
  void update(const ASGE::GameTime& us) override;
  void render(const ASGE::GameTime& us, ASGE::Renderer* renderer = nullptr) override;
  void removeState() override;
  void init() override;

  void initMenuBG();
  void initMenuGraphics();
  void initMenuButtons(ASGE::Renderer* renderer);
  void initAudio();
  void menuGraphicsAnimation();
  void buttonsAnimation();
  void gamepadHandler();

 private:
  SoLoud::Wav title_bg_audio;

  float game_window_width  = 1920;
  float game_window_height = 1080;

  Buttons menu_buttons[2];
  int amount_menu_buttons = 0;
  float menu_button_anim_start[2];
  float anim_frames = 600;
  float anim_step   = 0;

  bool gamepad_one_button_press = false;
  bool gamepad_two_button_press = false;

  GameObject title_card;
  float title_card_anim_start = 0;

  GameObject bg_moving;
  float bg_moving_anim_start  = 0;
  float bg_moving_anim_frames = 1800;
  float bg_moving_anim_step   = 0;

  //  std::unique_ptr<ASGE::Sprite> title_card = nullptr;
};

#endif // ASGEGAME_TITLESTATE_H
