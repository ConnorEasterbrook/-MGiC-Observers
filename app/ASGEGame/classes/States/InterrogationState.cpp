//
// Created by crobi on 25/04/2022.
//

#include "InterrogationState.h"
#include "TitleState.h"
InterrogationState::InterrogationState(
  ASGE::Renderer* renderer, std::stack<State*>* gameStates, ASGE::Input* inputs, int score,
  Tiles* tiles) :
  State(renderer, gameStates, inputs),
  _score(score), ingame_font(renderer->loadFont("/data/fonts/machine-gunk.ttf", 42, 5))
{
  _tiles = tiles;
}
InterrogationState::~InterrogationState() = default;
void InterrogationState::inputHandler(ASGE::SharedEventData data)
{
  const auto* key  = dynamic_cast<const ASGE::KeyEvent*>(data.get());
  keymap[key->key] = key->action != ASGE::KEYS::KEY_RELEASED;

  // State Specific
  if (key->key == ASGE::KEYS::KEY_SPACE)
  {
    if (key->action == 1)
    {
      Logging::DEBUG("SPACE PRESSED");
      audio_engine.deinit();
      _gameStates->push(new TitleState(_renderer, _gameStates, _inputs));
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

  // Interrorgation Specific
  if (key->key == ASGE::KEYS::KEY_1 && key->action == ASGE::KEYS::KEY_RELEASED)
  {
    interrogation.setAnswerOption(1);
  }
  else if (key->key == ASGE::KEYS::KEY_2 && key->action == ASGE::KEYS::KEY_RELEASED)
  {
    interrogation.setAnswerOption(2);
  }
  else if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_RELEASED)
  {
    interrogation.keyHandlerInterrogation();
    if (interrogation.correct_answer_given)
    {
      _score = interrogation.addScore(_score);
    }
    interrogation.correct_answer_given = false;
  }
}

void InterrogationState::fixedUpdate(const ASGE::GameTime& us)
{
  Logging::DEBUG("InterrogationState FixedUpdate");
  // process single gamepad

  Logging::DEBUG("TitleState FixedUpdate");
  if (!initialized)
  {
    init();
  }

  gamepadHandler();
}
void InterrogationState::update(const ASGE::GameTime& us)
{
  score_text.setString("Score: " + std::to_string(_score));
  answer_option_text.setString(std::to_string(interrogation.getAnswerOption()));
}
void InterrogationState::render(const ASGE::GameTime& us, ASGE::Renderer* renderer)
{
  renderer->setClearColour(ASGE::COLOURS::ORANGERED);

  // reset the view and don't use a camera, useful for HUD
  renderer->setViewport(ASGE::Viewport{ 0, 0, 1920, 1080 });
  renderer->setProjectionMatrix(0, 0, 1920, 1080);
  interrogation.renderText(_renderer);

  setupTextRender(score_text, 10, 200, 600, ASGE::COLOURS::WHITE, 2);
  setupTextRender(answer_option_text, 10, 800, 600, ASGE::COLOURS::BLACK, 2);

  renderer->render(answer_option_text);
  renderer->render(score_text);
}
void InterrogationState::removeState()
{
  remove = true;
}

void InterrogationState::initInterrogation()
{
  interrogation.answerRNG(_tiles->hospital_furniture, _tiles->hospital_clocks);
  interrogation.initTextInit(_renderer);
}

void InterrogationState::initCameras()
{
  viewport1.y = 540;
  viewport1.x = 0;
  viewport1.h = 540;
  viewport1.w = 1920;

  viewport2.y = 0;
  viewport2.x = 0;
  viewport2.h = 540;
  viewport2.w = 1920;

  //  camera.lookAt(ASGE::Point2D(player.sprite()->getX(), player.sprite()->getY()));
  //  camera2.lookAt(ASGE::Point2D(playerTwo.sprite()->getX(), playerTwo.sprite()->getY()));
  // ASGE::Point2D look_at2 = ASGE::Point2D(player.sprite()->getX(), player.sprite()->getY() - 50);
  //  look_at2.x             = std::max(look_at2.x, 1280 * 0.5F); // left boundary
  //  look_at2.x             = std::min(look_at2.x, 9450.0F);     // right boundary
  // camera2.lookAt(look_at2);
}

void InterrogationState::setupTextRender(
  ASGE::Text& text, int16_t z_order, float x_pos, float y_pos, ASGE::Colour colour, float scale)
{
  text.setFont(*ingame_font);
  text.setZOrder(z_order);
  text.setPositionX(x_pos);
  text.setPositionY(y_pos);
  text.setColour(colour);
  text.setScale(scale);
}

void InterrogationState::gamepadHandler()
{
  auto gamepadOne = _inputs->getGamePad();
  if (gamepadOne.is_connected)
  {
    if (gamepadOne.axis[0] > 0.1 && interrogation.getAnswerOption() < 2)
    {
      interrogation.setAnswerOption(interrogation.getAnswerOption() + 1);
    }
    else if (gamepadOne.axis[0] < -0.1 && interrogation.getAnswerOption() > 1)
    {
      interrogation.setAnswerOption(interrogation.getAnswerOption() + 1);
    }
    if (gamepadOne.buttons[ASGE::GAMEPAD::BUTTON_A] == 1)
    {
      interrogation.keyHandlerInterrogation();
      if (interrogation.correct_answer_given)
      {
        _score = interrogation.addScore(_score);
      }
      interrogation.correct_answer_given = false;
      interrogation.setAnswerOption(0);
    }
  }

  auto gamepadTwo = _inputs->getGamePad(1);
  if (gamepadTwo.is_connected)
  {
    // Do Player/Gamepad 2 Stuff
  }

  //  if (auto gamepad = _inputs->getGamePad(); gamepad.is_connected)
  //  {
  //    if (_gamepad_state.contains(gamepad.idx))
  //    {
  //      if (
  //        ((gamepad.buttons[ASGE::GAMEPAD::BUTTON_X]) == 0U) &&
  //        ((_gamepad_state.at(gamepad.idx).buttons[ASGE::GAMEPAD::BUTTON_X]) != 0U))
  //      {
  //        Logging::DEBUG("X PRESSED");
  //      }
  //    }
  //  }

  // retrieve all connected gamepads and store their gameStates
}
void InterrogationState::init()
{
  audio_engine.init();
  ASGE::FILEIO::File interrogation_audio_file;
  if (interrogation_audio_file.open("/data/audio/InterrogationMusic.mp3"))
  {
    auto buffer = interrogation_audio_file.read();
    auto length = static_cast<unsigned int>(buffer.length);
    interrogation_music.loadMem(buffer.as_unsigned_char(), length, false, false);
    interrogation_music.setVolume(1);
    interrogation_music.setLooping(true);
    Logging::WARN("Interrogation Music Loaded");
  }
  audio_engine.play(interrogation_music);

  initCameras();
  initInterrogation();
  for (auto& gamepad : _inputs->getGamePads())
  {
    _gamepad_state.insert_or_assign(gamepad.idx, gamepad);
  }
  initialized = true;
}
