//
// Created by crobi on 26/04/2022.
//

#include "HospitalState.h"

#include "InterrogationState.h"
#include "MainGameState.h"
#include "PauseState.h"
#include "TitleState.h"

HospitalState::HospitalState(
  ASGE::Renderer* renderer, std::stack<State*>* gameStates, ASGE::Input* inputs) :
  State(renderer, gameStates, inputs),
  ingame_font(renderer->loadFont("/data/fonts/machine-gunk.ttf", 42, 5))
{
  // renderer->setClearColour(ASGE::COLOURS::CORNFLOWERBLUE);
}

HospitalState::~HospitalState() = default;
void HospitalState::inputHandler(ASGE::SharedEventData data)
{
  const auto* key  = dynamic_cast<const ASGE::KeyEvent*>(data.get());
  keymap[key->key] = key->action != ASGE::KEYS::KEY_RELEASED;

  keyHandlerPlayer(key);

  // Default State Keys
  if (key->key == ASGE::KEYS::KEY_SPACE)
  {
    if (key->action == 1)
    {
      Logging::DEBUG("SPACE PRESSED");
      audio_engine.deinit();
      _gameStates->push(new InterrogationState(_renderer, _gameStates, _inputs, score, &tiles));
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

void HospitalState::fixedUpdate(const ASGE::GameTime& us)
{
  if (!initialized)
  {
    init();
  }
  gamepadHandler();

  if (
    tiles.getWalkable(player) && !tiles.getCollidables(player) && !tiles.getLeftTile(player) &&
    !tiles.getRightTile(player) && !tiles.getEndTile(player))
  {
    p1_old_x_pos = player.sprite()->getX();
    p1_old_y_pos = player.sprite()->getY();
  }
  else if (tiles.getEndTile(player))
  {
    audio_engine.deinit();
    _gameStates->push(new InterrogationState(_renderer, _gameStates, _inputs, score, &tiles));
    // game_state = GameState::INTERROGATION;
    // interrogation.answerRNG(tiles.hospital_furniture, tiles.hospital_clocks);
  }
  else
  {
    player.sprite()->setX(p1_old_x_pos);
    player.sprite()->setY(p1_old_y_pos);
  }

  if (
    tiles.getWalkable(playerTwo) && !tiles.getCollidables(playerTwo) &&
    !tiles.getLeftTile(playerTwo) && !tiles.getRightTile(playerTwo) && !tiles.getEndTile(playerTwo))
  {
    p2_old_x_pos = playerTwo.sprite()->getX();
    p2_old_y_pos = playerTwo.sprite()->getY();
  }
  else if (tiles.getEndTile(playerTwo))
  {
    audio_engine.deinit();
    _gameStates->push(new InterrogationState(_renderer, _gameStates, _inputs, score, &tiles));
    // game_state = GameState::INTERROGATION;
    // interrogation.answerRNG(tiles.hospital_furniture, tiles.hospital_clocks);
  }
  else
  {
    playerTwo.sprite()->setX(p2_old_x_pos);
    playerTwo.sprite()->setY(p2_old_y_pos);
  }

  // Logging::DEBUG("HospitalState FixedUpdate");
}

void HospitalState::update(const ASGE::GameTime& us)
{
  //  ASGE::Point2D look_at2 = ASGE::Point2D(player.sprite()->getX(), player.sprite()->getY() - 50);
  //  camera2.lookAt(look_at2);
  camera.lookAt(ASGE::Point2D(player.sprite()->getX(), player.sprite()->getY()));
  camera2.lookAt(ASGE::Point2D(playerTwo.sprite()->getX(), playerTwo.sprite()->getY()));

  updateHospitalMap(us);
  player.playerUpdate(us);
  playerTwo.playerUpdate(us);
  // player.playerCollisions(tiles.getTile("collidable"), tiles.getTileScale());
}

void HospitalState::render(const ASGE::GameTime& us, ASGE::Renderer* renderer)
{
  renderer->setClearColour(ASGE::COLOURS::CORNFLOWERBLUE);

  renderer->setViewport(viewport1);
  renderer->setProjectionMatrix(camera.getView());

  player.goRender(renderer, 10 * (player.sprite()->getY() + player.sprite()->getTrueHeight()));
  playerTwo.goRender(
    renderer, 10 * (playerTwo.sprite()->getY() + player.sprite()->getTrueHeight()));
  qObject->render(1);
  renderHospitalMap();

  renderer->setViewport(viewport2);
  renderer->setProjectionMatrix(camera2.getView());

  player.goRender(renderer, 31000);
  playerTwo.goRender(renderer, 31000);
  qObject->render(2);
  renderHospitalMap();

  // reset the view and don't use a camera, useful for HUD
  renderer->setViewport(ASGE::Viewport{ 0, 0, 1920, 1080 });
  renderer->setProjectionMatrix(0, 0, 1920, 1080);

  game_timer_text.setString(std::to_string(game_timer));
  setupTextRender(game_timer_text, 31000, 1920 - 300, 50, ASGE::COLOURS::BLACK, 1);

  setupTextRender(score_text, 31000, 10, 100, ASGE::COLOURS::WHITE, 2);
  _renderer->render(game_timer_text);
  _renderer->render(score_text);
}

void HospitalState::removeState()
{
  remove = true;
}

void HospitalState::initHospitalMap()
{
  tiles.initTileInit(_renderer);
}
void HospitalState::initPlayer()
{
  player.addSpriteComponent(
    "data/sprites/player_ship.png", std::make_unique<SpriteComponent>(), _renderer, 10);

  if (player.sprite()->getSprite() != nullptr)
  {
    player.sprite()->setDimensions(16, 16, 3);
    player.sprite()->setBounds(80, 32);
  }
  player.selectSprite();

  player.setPlayerSpawn(115, 585);
  player.teleportPlayerSpawn();

  player.visibility = true;

  playerTwo.addSpriteComponent(
    "data/sprites/player_ship.png", std::make_unique<SpriteComponent>(), _renderer, 10);

  if (playerTwo.sprite()->getSprite() != nullptr)
  {
    playerTwo.sprite()->setDimensions(16, 16, 3);
    playerTwo.sprite()->setBounds(80, 32);
  }
  playerTwo.selectSprite();

  playerTwo.setPlayerSpawn(155, 585);
  playerTwo.teleportPlayerSpawn();

  playerTwo.visibility = true;
}
void HospitalState::initCameras()
{
  viewport1.y = 540;
  viewport1.x = 0;
  viewport1.h = 540;
  viewport1.w = 1920;

  viewport2.y = 0;
  viewport2.x = 0;
  viewport2.h = 540;
  viewport2.w = 1920;

  camera.lookAt(ASGE::Point2D(player.sprite()->getX(), player.sprite()->getY()));
  camera2.lookAt(ASGE::Point2D(playerTwo.sprite()->getX(), playerTwo.sprite()->getY()));
  // ASGE::Point2D look_at2 = ASGE::Point2D(player.sprite()->getX(), player.sprite()->getY() - 50);
  //  look_at2.x             = std::max(look_at2.x, 1280 * 0.5F); // left boundary
  //  look_at2.x             = std::min(look_at2.x, 9450.0F);     // right boundary
  // camera2.lookAt(look_at2);
}

void HospitalState::updateHospitalMap(const ASGE::GameTime& us)
{
  countdown -= static_cast<float>(us.deltaInSecs());
  game_timer = static_cast<int>(countdown);
  score_text.setString("Score: " + std::to_string(score));
  if (score > 0)
  {
    score = (SECONDS_PENALTY * game_timer);
  }
}

void HospitalState::renderHospitalMap()
{
  tiles.renderTiles(_renderer);
}

void HospitalState::setupTextRender(
  ASGE::Text& text, int16_t z_order, float x_pos, float y_pos, ASGE::Colour colour, float scale)
{
  text.setFont(*ingame_font);
  text.setZOrder(z_order);
  text.setPositionX(x_pos);
  text.setPositionY(y_pos);
  text.setColour(colour);
  text.setScale(scale);
}

void HospitalState::keyHandlerPlayer(const auto* key)
{
  if (player.visibility)
  {
    if (key->key == ASGE::KEYS::KEY_W && key->action == ASGE::KEYS::KEY_PRESSED)
    {
      player.upMovementKey = true;
    }
    if (key->key == ASGE::KEYS::KEY_W && key->action == ASGE::KEYS::KEY_RELEASED)
    {
      player.upMovementKey = false;
    }
    if (key->key == ASGE::KEYS::KEY_S && key->action == ASGE::KEYS::KEY_RELEASED)
    {
      player.downMovementKey = false;
    }
    if (key->key == ASGE::KEYS::KEY_S && key->action == ASGE::KEYS::KEY_PRESSED)
    {
      player.downMovementKey = true;
    }
    if (key->key == ASGE::KEYS::KEY_A && key->action == ASGE::KEYS::KEY_PRESSED)
    {
      player.leftMovementKey = true;
    }
    if (key->key == ASGE::KEYS::KEY_A && key->action == ASGE::KEYS::KEY_RELEASED)
    {
      player.leftMovementKey = false;
    }
    if (key->key == ASGE::KEYS::KEY_D && key->action == ASGE::KEYS::KEY_RELEASED)
    {
      player.rightMovementKey = false;
    }
    if (key->key == ASGE::KEYS::KEY_D && key->action == ASGE::KEYS::KEY_PRESSED)
    {
      player.rightMovementKey = true;
    }
  }
}
void HospitalState::gamepadHandler()
{
  if (auto gamepad = _inputs->getGamePad(); gamepad.is_connected)
  {
    if (_gamepad_state.contains(gamepad.idx))
    {
      if (
        ((gamepad.buttons[ASGE::GAMEPAD::BUTTON_START]) == 0U) &&
        ((_gamepad_state.at(gamepad.idx).buttons[ASGE::GAMEPAD::BUTTON_START]) != 0U))
      {
        Logging::DEBUG("START PRESSED - Pausing");
        _gameStates->push(new PauseState(_renderer, _gameStates, _inputs, &audio_engine));
        // audio_engine.setGlobalVolume(0);
        // audio_engine.deinit();
        //        audio_engine.stopAll();
      }
    }
  }
  // retrieve all connected gamepads and store their states
  for (auto& gamepad : _inputs->getGamePads())
  {
    _gamepad_state.insert_or_assign(gamepad.idx, gamepad);
  }

  auto gamepadOne = _inputs->getGamePad();
  if (gamepadOne.is_connected)
  {
    if (std::abs(gamepadOne.axis[ASGE::GAMEPAD::AXIS_LEFT_X]) > 0.15)
    {
      velocity.x = gamepadOne.axis[ASGE::GAMEPAD::AXIS_LEFT_X] * 300;
    }
    else
    {
      velocity.x = 0;
    }
    if (std::abs(gamepadOne.axis[ASGE::GAMEPAD::AXIS_LEFT_Y]) > 0.15)
    {
      velocity.y = gamepadOne.axis[ASGE::GAMEPAD::AXIS_LEFT_Y] * 300;
    }
    else
    {
      velocity.y = 0;
    }
    player.gamepadInput(velocity);
  }

  auto gamepadTwo = _inputs->getGamePad(1);
  if (gamepadTwo.is_connected)
  {
    if (std::abs(gamepadTwo.axis[ASGE::GAMEPAD::AXIS_LEFT_X]) > 0.15)
    {
      velocityTwo.x = gamepadTwo.axis[ASGE::GAMEPAD::AXIS_LEFT_X] * 300;
    }
    else
    {
      velocityTwo.x = 0;
    }
    if (std::abs(gamepadTwo.axis[ASGE::GAMEPAD::AXIS_LEFT_Y]) > 0.15)
    {
      velocityTwo.y = gamepadTwo.axis[ASGE::GAMEPAD::AXIS_LEFT_Y] * 300;
    }
    else
    {
      velocityTwo.y = 0;
    }
    playerTwo.gamepadInput(velocityTwo);
  }
}
void HospitalState::init()
{
  initHospitalMap();
  initPlayer();
  initCameras();

  audio_engine.init();
  ASGE::FILEIO::File hospital_audio_file;
  if (hospital_audio_file.open("/data/audio/HospitalMap.mp3"))
  {
    auto buffer = hospital_audio_file.read();
    auto length = static_cast<unsigned int>(buffer.length);
    hospital_music.loadMem(buffer.as_unsigned_char(), length, false, false);
    hospital_music.setLooping(true);
    hospital_music.setVolume(1);
    Logging::WARN("Hospital Map Music Loaded");
  }
  audio_engine.play(hospital_music);

  qObject = std::make_unique<QuantomObject>(
    *_renderer, player.sprite()->getX() + 10, player.sprite()->getY() + 10);

  initialized = true;
}
