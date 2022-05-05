//
// Created by crobi on 25/04/2022.
//

#include "State.h"
State::State(ASGE::Renderer* renderer, std::stack<State*>* gameStates, ASGE::Input* inputs)
{
  initialized = false;
  quit        = false;
  remove      = false;
  _renderer   = renderer;
  _gameStates = gameStates;
  _inputs     = inputs;
}
State::~State()
{
  audio_engine.deinit();
}

const bool& State::isRemove() const
{
  return remove;
}

const bool& State::quitState() const
{
  return quit;
}

void State::init() {}
bool State::isReturnToTitle() const
{
  return returnToTitle;
}
