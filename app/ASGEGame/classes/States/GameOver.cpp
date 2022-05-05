//
// Created by crobi on 28/04/2022.
//

#include "GameOver.h"

GameOver::GameOver(ASGE::Renderer* renderer, std::stack<State*>* gameStates, ASGE::Input* inputs) :
  State(renderer, gameStates, inputs)
{
}
GameOver::~GameOver() = default;
void GameOver::inputHandler(ASGE::SharedEventData data)
{
  const auto* key  = dynamic_cast<const ASGE::KeyEvent*>(data.get());
  keymap[key->key] = key->action != ASGE::KEYS::KEY_RELEASED;

  if (key->key == ASGE::KEYS::KEY_SPACE)
  {
    if (key->action == 1)
    {
      Logging::DEBUG("SPACE PRESSED");
      //_gameStates->push(new TitleState(_renderer, _gameStates, _inputs));
    }
  }
  if (key->key == ASGE::KEYS::KEY_ESCAPE)
  {
    if (key->action == 1)
    {
      Logging::DEBUG("ESC PRESSED");
      removeState();
    }
  }
}
void GameOver::fixedUpdate(const ASGE::GameTime& us)
{
  Logging::DEBUG("GameWon FixedUpdate");
  // process single gamepad
  if (auto gamepad = _inputs->getGamePad(); gamepad.is_connected)
  {
    if (_gamepad_state.contains(gamepad.idx))
    {
      if (
        ((gamepad.buttons[ASGE::GAMEPAD::BUTTON_X]) == 0U) &&
        ((_gamepad_state.at(gamepad.idx).buttons[ASGE::GAMEPAD::BUTTON_X]) != 0U))
      {
        Logging::DEBUG("X PRESSED");
      }
    }
  }

  // retrieve all connected gamepads and store their gameStates
  for (auto& gamepad : _inputs->getGamePads())
  {
    _gamepad_state.insert_or_assign(gamepad.idx, gamepad);
  }
  if (!initialized)
  {
    init();
  }
}
void GameOver::update(const ASGE::GameTime& us) {}
void GameOver::render(const ASGE::GameTime& us, ASGE::Renderer* renderer)
{
  renderer->setClearColour(ASGE::COLOURS::RED);
}
void GameOver::removeState()
{
  quit = true;
}
void GameOver::init()
{
  _renderer->setClearColour(ASGE::COLOURS::RED);
}
