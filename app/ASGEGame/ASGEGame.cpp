#include "ASGEGame.hpp"
#include <Engine/FileIO.hpp>
#include <Engine/Logger.hpp>

/**
 * @brief Initialises the game.
 * Setup your game and initialise the core components.
 * @param settings
 */
ASGENetGame::ASGENetGame(const ASGE::GameSettings& settings) :
  OGLGame(settings), game_font(renderer->loadFont("/data/fonts/machine-gunk.ttf", 42, 5))
{
  renderer->setBaseResolution(1920, 1080, ASGE::Resolution::Policy::MAINTAIN);
  key_callback_id   = inputs->addCallbackFnc(ASGE::E_KEY, &ASGENetGame::keyHandler, this);
  mouse_callback_id = inputs->addCallbackFnc(ASGE::E_MOUSE_CLICK, &ASGENetGame::clickHandler, this);
  inputs->use_threads = false;

  ship = renderer->createUniqueSprite();
  ship->loadTexture("/data/sprites/player_ship.png");

  camera_one_label.setFont(*game_font).setString("Camera 1").setPosition({ 0, 55 }).setScale(1.5);
  camera_two_label.setFont(*game_font).setString("Camera 2").setPosition({ 960, 55 }).setScale(1.5);

  init();
}

void ASGENetGame::init()
{
  game_font = renderer->loadFont("data/fonts/machine-gunk.ttf", 18);

  initAudio();
  initGame();
}

void ASGENetGame::initAudio()
{
  audio_engine.init();
  ASGE::FILEIO::File bg_audio_file;
  if (bg_audio_file.open("/data/audio/cyberpunk.mp3"))
  {
    auto buffer = bg_audio_file.read();
    auto length = static_cast<unsigned int>(buffer.length);
    background_audio.loadMem(buffer.as_unsigned_char(), length, false, false);
    background_audio.setLooping(true);
    audio_engine.play(background_audio);
  }
}

void ASGENetGame::initGame()
{
  initPlayer();
  initHospitalMap();
}

void ASGENetGame::initPlayer()
{
  player.addSpriteComponent(
    "data/sprites/player_ship.png", std::make_unique<SpriteComponent>(), renderer.get(), 10);

  if (player.sprite()->getSprite() != nullptr)
  {
    player.sprite()->setDimensions(16, 16, 3);
    player.sprite()->setBounds(80, 32);
  }

  player.setPlayerSpawn(115, 585);
  player.teleportPlayerSpawn();

  player.visibility = true;
}

void ASGENetGame::initHospitalMap()
{
  tiles.initTileInit(renderer.get());
}

/**
 * Destroys the game.
 */
ASGENetGame::~ASGENetGame()
{
  this->inputs->unregisterCallback(key_callback_id);
  audio_engine.deinit();
}

/**
 * @brief Processes key inputs.
 * This function is added as a callback to handle the game's
 * keyboard input. For this game, calls to this function
 * are not thread safe, so you may alter the game's state
 * but your code needs to designed to prevent data-races.
 *
 * @param data
 * @see KeyEvent
 */
void ASGENetGame::keyHandler(ASGE::SharedEventData data)
{
  const auto* key  = dynamic_cast<const ASGE::KeyEvent*>(data.get());
  keymap[key->key] = key->action != ASGE::KEYS::KEY_RELEASED;

  if (key->key == ASGE::KEYS::KEY_ESCAPE)
  {
    signalExit();
  }

  if (key->key == ASGE::KEYS::KEY_P && key->action == ASGE::KEYS::KEY_RELEASED)
  {
    split_screen = true;
  }

  if (key->key == ASGE::KEYS::KEY_O && key->action == ASGE::KEYS::KEY_RELEASED)
  {
    general_state = GeneralState::GAME;
  }

  if (key->key == ASGE::KEYS::KEY_I && key->action == ASGE::KEYS::KEY_RELEASED)
  {
    game_state = GameState::INTERROGATION;
  }

  if (key->key == ASGE::KEYS::KEY_U && key->action == ASGE::KEYS::KEY_RELEASED)
  {
    game_state = GameState::HOSPITAL_MAP;
  }

  if (general_state == GeneralState::GAME)
  {
    keyHandlerGame(key);
  }

  if (key->key == ASGE::KEYS::KEY_L && key->action == ASGE::KEYS::KEY_RELEASED)
  {
    player.selectSprite();
  }
}

void ASGENetGame::keyHandlerGame(const auto* key)
{
  keyHandlerPlayer(key);
}

void ASGENetGame::keyHandlerPlayer(const auto* key)
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

void ASGENetGame::clickHandler(ASGE::SharedEventData data)
{
  const auto* click = dynamic_cast<const ASGE::ClickEvent*>(data.get());

  double x_pos = click->xpos;
  double y_pos = click->ypos;

  if (click->action == ASGE::KEYS::KEY_PRESSED)
  {
    Logging::DEBUG("x_pos: " + std::to_string(x_pos));
    Logging::DEBUG("y_pos: " + std::to_string(y_pos));
  }
}

/**
 * @brief FixedUpdate
 * Calls to this function use the same fixed timestep
 * irrespective of how much time is passed. If you want
 * deterministic behaviour on clients, this is the place
 * to go.
 *
 * https://gamedev.stackexchange.com/questions/1589/when-should-i-use-a-fixed-or-variable-time-step
 * "Use variable timesteps for your fixed steps for physics"
 * @param us
 */
void ASGENetGame::fixedUpdate(const ASGE::GameTime& us)
{
  Game::fixedUpdate(us);
}

/**
 * @brief Updates your game and all it's components.
 * @param us
 */
void ASGENetGame::update(const ASGE::GameTime& us)
{
  // process single gamepad
  if (auto gamepad = inputs->getGamePad(); gamepad.is_connected)
  {
    velocity.x = gamepad.axis[ASGE::GAMEPAD::AXIS_LEFT_X] * 500;
    velocity.y = gamepad.axis[ASGE::GAMEPAD::AXIS_LEFT_Y] * 500;

    if (gamepad_state.contains(gamepad.idx))
    {
      if (
        ((gamepad.buttons[ASGE::GAMEPAD::BUTTON_X]) == 0U) &&
        ((gamepad_state.at(gamepad.idx).buttons[ASGE::GAMEPAD::BUTTON_X]) != 0U))
      {
        Logging::DEBUG("X PRESSED");
        velocity.y *= 10;
      }
    }

    if (general_state == MENU)
    {
      updateMenu();
      joystickMenuInput(gamepad);
    }
    else if (general_state == GAME)
    {
      updateGame(us);
      player.gamepadInput(velocity);
      if (tiles.getWalkable(player) && !tiles.getCollidables(player))
      {
        old_x_pos = player.sprite()->getX();
        old_y_pos = player.sprite()->getY();
      }
      else
      {
        player.sprite()->setX(old_x_pos);
        player.sprite()->setY(old_y_pos);

        std::cout << "OUT OF BOUNDS" << std::endl;
      }

      //      player.playerCollisions(tiles.getTile("collidable"), tiles.getTileScale());
    }
  }

  ship->xPos(static_cast<float>(ship->xPos() + velocity.x * us.deltaInSecs()));
  ship->yPos(static_cast<float>(ship->yPos() + velocity.y * us.deltaInSecs()));

  // retrieve all connected gamepads and store their states
  for (auto& gamepad : inputs->getGamePads())
  {
    gamepad_state.insert_or_assign(gamepad.idx, gamepad);
  }
}

void ASGENetGame::updateMenu() {}

void ASGENetGame::updateGame(const ASGE::GameTime& us)
{
  camera_one.lookAt(ASGE::Point2D{
    static_cast<float>(
      player.sprite()->getX() +
      (player.sprite()->getSprite()->width() * player.sprite()->getSprite()->scale() / 2)),
    static_cast<float>(
      player.sprite()->getY() +
      (player.sprite()->getSprite()->height() * player.sprite()->getSprite()->scale() / 2)) });

  if (game_state == GameState::BASE_GAMEPLAY)
  {
    updateBaseGame();
    player.playerUpdate(us);
  }
  else if (game_state == GameState::INTERROGATION)
  {
    updateInterrogation();
  }
  else if (game_state == GameState::HOSPITAL_MAP)
  {
    updateHospitalMap();
    player.playerUpdate(us);
  }
}

void ASGENetGame::updateBaseGame() {}

void ASGENetGame::updateInterrogation() {}

void ASGENetGame::updateHospitalMap() {}

void ASGENetGame::joystickMenuInput(auto joystick)
{
  if (joystick.buttons[0] != 0)
  {
    //    if (menu_option == 0)
    //    {
    //      in_menu = false;
    //      in_game = true;
    //    }
    //    else if (menu_option == 1)
    //    {
    //      signalExit();
    //    }
  }

  if (joystick.axis[1] > -0.2)
  {
    //    if (menu_option <= 0)
    //    {
    //      menu_option = 1;
    //    }
  }
  if (joystick.axis[1] < 0.2)
  {
    //    if (menu_option >= 1)
    //    {
    //      menu_option = 0;
    //    }
  }
}

/**
 * @brief Render your game and its scenes here.
 * @param us
 */
void ASGENetGame::render(const ASGE::GameTime& /*us*/)
{
  if (general_state == MENU)
  {
    renderMenu();
  }
  else if (general_state == GAME)
  {
    renderGame();
  }
}

void ASGENetGame::renderMenu() {}

void ASGENetGame::renderGame()
{
  if (!split_screen)
  {
    camera_one.setZoom(2);
    camera_one.resize(1920, 1080);
    renderer->setProjectionMatrix(camera_one.getView());
  }

  if (game_state == GameState::BASE_GAMEPLAY)
  {
    player.goRender(renderer.get(), 1);

    if (split_screen)
    {
      renderSplitScreen();
    }
  }
  else if (game_state == GameState::INTERROGATION)
  {
    renderInterrogation();
  }
  else if (game_state == GameState::HOSPITAL_MAP)
  {
    player.goRender(renderer.get(), 1);
    renderHospitalMap();
  }
}

void ASGENetGame::renderSplitScreen()
{
  // example of split screen. just remove viewports and use
  // a single camera if you don't require the use of split screen
  renderer->setViewport(ASGE::Viewport{ 0, 0, 960, 1080 });
  renderer->setProjectionMatrix(camera_one.getView());
  renderer->render(*ship);
  renderer->setViewport(ASGE::Viewport{ 960, 0, 960, 1080 });
  renderer->setProjectionMatrix(camera_two.getView());
  renderer->render(*ship);

  // reset the view and don't use a camera, useful for HUD
  renderer->setViewport(ASGE::Viewport{ 0, 0, 1920, 1080 });
  renderer->setProjectionMatrix(0, 0, 1920, 1080);
  renderer->render(camera_one_label);
  renderer->render(camera_two_label);
}

void ASGENetGame::renderInterrogation() {}

void ASGENetGame::renderHospitalMap()
{
  tiles.renderTiles(renderer.get());
}

void ASGENetGame::setupInitSprites(
  std::unique_ptr<ASGE::Sprite>& sprite, const std::string& texture_file_path, float width,
  float height, int16_t z_order, float x_pos, float y_pos, float scale)
{
  sprite = renderer->createUniqueSprite();
  sprite->loadTexture(texture_file_path);

  if (!sprite->loadTexture(texture_file_path))
  {
    std::cout << "SPRITE FAILED TO INITIALISE" << std::endl;
    return;
  }

  sprite->height(height);
  sprite->width(width);
  sprite->setGlobalZOrder(z_order);
  sprite->xPos(x_pos);
  sprite->yPos(y_pos);
  sprite->scale(scale);

  sprite->setMagFilter(ASGE::Texture2D::MagFilter::NEAREST);
}

void ASGENetGame::setupTextRender(
  ASGE::Text& text, int16_t z_order, float x_pos, float y_pos, ASGE::Colour colour)
{
  text.setFont(*game_font);
  text.setZOrder(z_order);
  text.setPositionX(x_pos);
  text.setPositionY(y_pos);
  text.setColour(colour);
}
