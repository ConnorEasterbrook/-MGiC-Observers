//
// Created by crobi on 28/04/2022.
//

#ifndef ASGEGAME_GAMEWON_H
#define ASGEGAME_GAMEWON_H

#include "State.h"
class GameWon : public State
{
 public:
  explicit GameWon(ASGE::Renderer* renderer, std::stack<State*>* gameStates, ASGE::Input* inputs);
  virtual ~GameWon() override;

  void inputHandler(ASGE::SharedEventData data) override;
  void fixedUpdate(const ASGE::GameTime& us) override;
  void update(const ASGE::GameTime& us) override;
  void render(const ASGE::GameTime& us, ASGE::Renderer* renderer = nullptr) override;
  void removeState() override;
  void init() override;

 private:
};

#endif // ASGEGAME_GAMEWON_H
