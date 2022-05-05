//
// Created by crobi on 28/04/2022.
//

#ifndef ASGEGAME_PAUSESTATE_H
#define ASGEGAME_PAUSESTATE_H

#include "State.h"
class PauseState : public State
{
 public:
  explicit PauseState(
    ASGE::Renderer* renderer, std::stack<State*>* gameStates, ASGE::Input* inputs,
    SoLoud::Soloud* current_audio_engine);
  virtual ~PauseState() override;

  void inputHandler(ASGE::SharedEventData data) override;
  void fixedUpdate(const ASGE::GameTime& us) override;
  void update(const ASGE::GameTime& us) override;
  void render(const ASGE::GameTime& us, ASGE::Renderer* renderer = nullptr) override;
  void removeState() override;
  void init() override;
  void gamepadHandler();

  std::unique_ptr<ASGE::Sprite> pauseBG;

 protected:
  SoLoud::Soloud* _current_audio_engine;
  bool muted = false;
};

#endif // ASGEGAME_PAUSESTATE_H
