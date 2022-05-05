//
// Created by crobi on 25/04/2022.
//

#ifndef ASGEGAME_MAINGAMESTATE_H
#define ASGEGAME_MAINGAMESTATE_H

#include "State.h"

class MainGameState : public State
{
 public:
  explicit MainGameState(
    ASGE::Renderer* renderer, std::stack<State*>* gameStates, ASGE::Input* inputs);
  virtual ~MainGameState() override;

  void inputHandler(ASGE::SharedEventData data) override;
  void fixedUpdate(const ASGE::GameTime& us) override;
  void update(const ASGE::GameTime& us) override;
  void render(const ASGE::GameTime& us, ASGE::Renderer* renderer = nullptr) override;
  void removeState() override;
  void init() override;

 private:
};

#endif // ASGEGAME_MAINGAMESTATE_H
