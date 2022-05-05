//
// Created by crobi on 25/04/2022.
//

#ifndef ASGEGAME_STATE_H
#define ASGEGAME_STATE_H

#include <Engine/FileIO.hpp>
#include <Engine/Gamepad.hpp>
#include <Engine/Logger.hpp>
#include <Engine/OGLGame.hpp>
#include <Engine/Sprite.hpp>
#include <map>
#include <soloud.h>
#include <soloud_wav.h>
#include <stack>
#include <vector>

class State
{
 public:
  State(ASGE::Renderer* renderer, std::stack<State*>* gameStates, ASGE::Input* inputs);
  virtual ~State();

  // Pure Virtual Functions - ensures any class that inherits from this class
  // must define these functions
  virtual void inputHandler(ASGE::SharedEventData data)                             = 0;
  virtual void fixedUpdate(const ASGE::GameTime& us)                                = 0;
  virtual void update(const ASGE::GameTime& us)                                     = 0;
  virtual void render(const ASGE::GameTime& us, ASGE::Renderer* renderer = nullptr) = 0;
  virtual void init()                                                               = 0;

  virtual void removeState() = 0;
  [[nodiscard]] const bool& quitState() const;
  [[nodiscard]] const bool& isRemove() const;

 private:
  // input
  std::string key_callback_id{}; /**< Key Input Callback ID. */

 protected:
  // AUDIO
  SoLoud::Soloud audio_engine;
  ASGE::Renderer* _renderer;
  std::stack<State*>* _gameStates;
  std::map<int, bool> keymap{};
  bool remove;
  bool quit;
  ASGE::Input* _inputs;
  std::map<int, ASGE::GamePadData> _gamepad_state{};
  bool initialized   = false;
  bool returnToTitle = false;

 public:
  bool isReturnToTitle() const;
};

#endif // ASGEGAME_STATE_H
