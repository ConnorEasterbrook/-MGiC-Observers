#include "ASGEGame.hpp"
#include <classes/States/TitleState.h>

/**
 * @brief Initialises the game.
 * Setup your game and initialise the core components.
 * @param settings
 */
ASGENetGame::ASGENetGame(const ASGE::GameSettings& settings) :
  OGLGame(settings), game_font(renderer->loadFont("/data/fonts/machine-gunk.ttf", 42, 5))
{
  renderer->setBaseResolution(1920, 1080, ASGE::Resolution::Policy::MAINTAIN);
  key_callback_id     = inputs->addCallbackFnc(ASGE::E_KEY, &ASGENetGame::keyHandler, this);
  inputs->use_threads = true;
  gameStates.push(new TitleState(renderer.get(), &gameStates, inputs.get()));
}

/**
 * Destroys the game.
 */
ASGENetGame::~ASGENetGame()
{
  this->inputs->unregisterCallback(key_callback_id);

  while (!gameStates.empty())
  {
    delete gameStates.top();
    gameStates.pop();
  }
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
  if (!gameStates.empty())
  {
    gameStates.top()->inputHandler(data);
  }
  //  if (key->key == ASGE::KEYS::KEY_T && key->action == ASGE::KEYS::KEY_RELEASED)
  //  {
  //    start_pos_lerp = LerpTest->xPos();
  //    end_pos_lerp = 540;
  //    lerp_test = true;
  //  }
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

  if (!gameStates.empty())
  {
    gameStates.top()->fixedUpdate(us);
  }
}

/**
 * @brief Updates your game and all it's components.
 * @param us
 */
void ASGENetGame::update(const ASGE::GameTime& us)
{
  if (!gameStates.empty())
  {
    gameStates.top()->update(us);

    if (gameStates.top()->isRemove())
    {
      gameStates.top()->removeState();
      delete gameStates.top();
      gameStates.pop();
    }
    else if (gameStates.top()->quitState())
    {
      signalExit();
    }
    else if (gameStates.top()->isReturnToTitle())
    {
      // do stuff...
    }
  }
  else
  {
    signalExit();
  }
}

/**
 * @brief Render your game and its scenes here.
 * @param us
 */
void ASGENetGame::render(const ASGE::GameTime& us)
{
  if (!gameStates.empty())
  {
    gameStates.top()->render(us, renderer.get());
  }
}

void ASGENetGame::initProjectiles()
{
  if (projectile.sprite()->getSprite() != nullptr)
    projectile.addSpriteComponent(
      "data/images/objects/laserRed.png", std::make_unique<SpriteComponent>(), renderer.get(), 11);
  projectile.sprite()->setDimensions(16, 8, 1);
  {
  }
  projectile.setProjectileDirection(1, 0);
  projectile.setProjectileSpeed(1);
  projectile.setProjectilePosition(1340, 1054);
  projectile.visibility = true;
  projectile.setProjectileSpawn();
  Logging::WARN("Projectile Initialized");
}