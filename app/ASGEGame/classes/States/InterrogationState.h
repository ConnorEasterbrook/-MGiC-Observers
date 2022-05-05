//
// Created by crobi on 25/04/2022.
//

#ifndef ASGEGAME_INTERROGATIONSTATE_H
#define ASGEGAME_INTERROGATIONSTATE_H

#include "State.h"
#include "classes/gameplay/Interrogation.h"
#include "classes/gameplay/InterrogationQuestion.hpp"
#include <classes/utility/Tiles.h>

class InterrogationState : public State
{
 public:
  explicit InterrogationState(
    ASGE::Renderer* renderer, std::stack<State*>* gameStates, ASGE::Input* inputs, int score,
    Tiles* tiles);
  virtual ~InterrogationState() override;

  void inputHandler(ASGE::SharedEventData data) override;
  void fixedUpdate(const ASGE::GameTime& us) override;
  void update(const ASGE::GameTime& us) override;
  void render(const ASGE::GameTime& us, ASGE::Renderer* renderer = nullptr) override;
  void removeState() override;
  void init() override;

  void initInterrogation();
  void initCameras();
  [maybe_unused] void setupTextRender(
    ASGE::Text& text, int16_t z_order, float x_pos, float y_pos, ASGE::Colour colour, float scale);

  void gamepadHandler();

  SoLoud::Wav interrogation_music;

 private:
  Interrogation interrogation;
  Tiles* _tiles;
  int _score;
  ASGE::Text score_text;
  ASGE::Text answer_option_text;

  ASGE::Camera camera{ 1280, 360 };
  ASGE::Camera camera2{ 1280, 360 };
  ASGE::Viewport viewport1;
  ASGE::Viewport viewport2;

  const ASGE::Font* ingame_font = nullptr;
};

#endif // ASGEGAME_INTERROGATIONSTATE_H
