//
// Created by crobi on 28/04/2022.
//

#include "PauseState.h"
PauseState::PauseState(
  ASGE::Renderer* renderer, std::stack<State*>* gameStates, ASGE::Input* inputs,
  SoLoud::Soloud* current_audio_engine) :
  State(renderer, gameStates, inputs)
{
  _current_audio_engine = current_audio_engine;
}
PauseState::~PauseState() {}

void PauseState::inputHandler(ASGE::SharedEventData data)
{
  const auto* key  = dynamic_cast<const ASGE::KeyEvent*>(data.get());
  keymap[key->key] = key->action != ASGE::KEYS::KEY_RELEASED;

  if (key->key == ASGE::KEYS::KEY_SPACE)
  {
    if (key->action == 1)
    {
      Logging::DEBUG("SPACE PRESSED");
      //      if (initialized)
      //      {
      //        //_gameStates->push(new HospitalState(_renderer, _gameStates, _inputs));
      //      }
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

void PauseState::fixedUpdate(const ASGE::GameTime& us)
{
  if (!initialized)
  {
    init();
  }

  gamepadHandler();
}
void PauseState::update(const ASGE::GameTime& us) {}
void PauseState::render(const ASGE::GameTime& us, ASGE::Renderer* renderer)
{
  if (initialized)
  {
    _renderer->render(*pauseBG);
  }
}
void PauseState::removeState()
{
  remove = true;
}
void PauseState::init()
{
  _renderer->setClearColour(ASGE::COLOURS::PURPLE);
  pauseBG = _renderer->createUniqueSprite();
  if (!pauseBG->loadTexture("/data/images/misc/PauseMenu.png"))
  {
    Logging::DEBUG("Pause Menu Texture Failed To Load!");
  }
  pauseBG->xPos(357);
  pauseBG->yPos(237);
  initialized = true;
}

void PauseState::gamepadHandler()
{
  if (auto gamepad = _inputs->getGamePad(); gamepad.is_connected)
  {
    if (_gamepad_state.contains(gamepad.idx))
    {
      if (
        ((gamepad.buttons[ASGE::GAMEPAD::BUTTON_X]) == 0U) &&
        ((_gamepad_state.at(gamepad.idx).buttons[ASGE::GAMEPAD::BUTTON_X]) != 0U))
      {
        Logging::DEBUG("X PRESSED - MUTING/UNMUTING");
        if (muted)
        {
          _current_audio_engine->setGlobalVolume(1);
          muted = false;
        }
        else
        {
          _current_audio_engine->setGlobalVolume(0);
          muted = true;
        }
      }
      if (
        ((gamepad.buttons[ASGE::GAMEPAD::BUTTON_START]) == 0U) &&
        ((_gamepad_state.at(gamepad.idx).buttons[ASGE::GAMEPAD::BUTTON_START]) != 0U))
      {
        Logging::DEBUG("START PRESSED - Unpausing");
        removeState();
      }
      if (
        ((gamepad.buttons[ASGE::GAMEPAD::BUTTON_Y]) == 0U) &&
        ((_gamepad_state.at(gamepad.idx).buttons[ASGE::GAMEPAD::BUTTON_Y]) != 0U))
      {
        Logging::DEBUG("Y PRESSED - Main Menu Shortcut Unimplemented");
        // returnToTitle = true;
      }
      if (
        ((gamepad.buttons[ASGE::GAMEPAD::BUTTON_BACK]) == 0U) &&
        ((_gamepad_state.at(gamepad.idx).buttons[ASGE::GAMEPAD::BUTTON_BACK]) != 0U))
      {
        Logging::DEBUG("SELECT/BACK PRESSED - Quitting");
        quit = true;
      }
    }
  }
  // retrieve all connected gamepads and store their states
  for (auto& gamepad : _inputs->getGamePads())
  {
    _gamepad_state.insert_or_assign(gamepad.idx, gamepad);
  }

  //  for (auto& gamepad : _inputs->getGamePads())
  //  {
  //    _gamepad_state.insert_or_assign(gamepad.idx, gamepad);
  //  }
  //  auto gamepadOne = _inputs->getGamePad();
  //  if (gamepadOne.is_connected)
  //  {
  //
  //  }
  //
  //  auto gamepadTwo = _inputs->getGamePad(1);
  //  if (gamepadTwo.is_connected)
  //  {
  //  }
}
