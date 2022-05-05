//
// Created by crobi on 26/04/2022.
//

#include "TitleState.h"
#include "HospitalState.h"
#include "MainGameState.h"

TitleState::TitleState(
  ASGE::Renderer* renderer, std::stack<State*>* gameStates, ASGE::Input* inputs) :
  State(renderer, gameStates, inputs)
{
  initMenuBG();
  initMenuGraphics();
  initMenuButtons(renderer);
  initAudio();
}

TitleState::~TitleState() {}

void TitleState::inputHandler(ASGE::SharedEventData data)
{
  const auto* key  = dynamic_cast<const ASGE::KeyEvent*>(data.get());
  keymap[key->key] = key->action != ASGE::KEYS::KEY_RELEASED;

  if (key->key == ASGE::KEYS::KEY_SPACE)
  {
    if (key->action == 1)
    {
      Logging::DEBUG("SPACE PRESSED");
      if (initialized)
      {
        audio_engine.deinit();
        _gameStates->push(new HospitalState(_renderer, _gameStates, _inputs));
      }
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

void TitleState::fixedUpdate(const ASGE::GameTime& us)
{
  if (!initialized)
  {
    init();
  }
  buttonsAnimation();
  gamepadHandler();
  menuGraphicsAnimation();
}

void TitleState::update(const ASGE::GameTime& us)
{
  if (menu_buttons[0].getState() == Buttons::READY && menu_buttons[1].getState() == Buttons::READY)
  {
    for (int i = 0; i < amount_menu_buttons; i++)
    {
      menu_buttons[i].setIsActive(false);
      menu_buttons[i].setState(Buttons::NOT_READY);
    }

    _gameStates->push(new HospitalState(_renderer, _gameStates, _inputs));
  }
}

void TitleState::render(const ASGE::GameTime& us, ASGE::Renderer* renderer)
{
  renderer->setClearColour(ASGE::COLOURS::DARKOLIVEGREEN);
  for (int i = 0; i < amount_menu_buttons; i++)
  {
    menu_buttons[i].goRender(renderer, 10);
    menu_buttons[i].goRender(renderer, 10);
  }
  title_card.goRender(renderer, 10);
  bg_moving.goRender(renderer, -5);
}

void TitleState::removeState()
{
  audio_engine.deinit();
  remove = true;
}

void TitleState::initMenuBG()
{
  bg_moving.addSpriteComponent(
    "data/images/misc/Observers_Title_State_Background.png",
    std::make_unique<SpriteComponent>(),
    _renderer,
    -5);
  bg_moving.visibility = true;
  bg_moving.sprite()->getSprite()->scale(2);
  bg_moving.sprite()->getSprite()->yPos(-540);

  bg_moving_anim_start = bg_moving.sprite()->getSprite()->xPos();
}

void TitleState::initMenuGraphics()
{
  title_card.addSpriteComponent(
    "data/images/misc/Observers_Title_Card.png", std::make_unique<SpriteComponent>(), _renderer, 10);
  title_card.sprite()->getSprite()->scale(6);
  title_card.sprite()->getSprite()->xPos(
    game_window_width / 2 -
    ((title_card.sprite()->getSprite()->width() * title_card.sprite()->getSprite()->scale()) / 2));
  title_card.sprite()->getSprite()->yPos(
    game_window_height / 2 -
    ((title_card.sprite()->getSprite()->height() * title_card.sprite()->getSprite()->scale()) / 2));
  title_card.sprite()->getSprite()->setMagFilter(ASGE::GameSettings::MagFilter::NEAREST);
  title_card.sprite()->getSprite()->setGlobalZOrder(10);
  title_card.visibility = true;

  title_card_anim_start = title_card.sprite()->getSprite()->yPos();
}

void TitleState::initMenuButtons(ASGE::Renderer* renderer)
{
  amount_menu_buttons = static_cast<int>(std::size(menu_buttons));

  for (int i = 0; i < amount_menu_buttons; i++)
  {
    menu_buttons[i].addSpriteComponent(
      "data/images/buttons/Start_Button_Alt_States.png",
      std::make_unique<SpriteComponent>(),
      renderer,
      1);
    menu_buttons[i].sprite()->getSprite()->xPos(
      (game_window_width / 2) -
      ((menu_buttons->getSpriteSheetWidth() * menu_buttons->getSpriteScaler()) / 2));
    if (i == 0)
    {
      menu_buttons[i].sprite()->getSprite()->yPos(
        (game_window_height / 4) -
        ((menu_buttons->getSpriteSheetHeight() * menu_buttons->getSpriteScaler()) / 2));
    }
    else if (i == 1)
    {
      menu_buttons[i].sprite()->getSprite()->yPos(
        (3 * game_window_height / 4) -
        ((menu_buttons->getSpriteSheetHeight() * menu_buttons->getSpriteScaler()) / 2));
    }
    menu_button_anim_start[i] = menu_buttons[i].sprite()->getSprite()->yPos();
    menu_buttons[i].sprite()->getSprite()->setMagFilter(ASGE::GameSettings::MagFilter::NEAREST);
  }
}

void TitleState::initAudio()
{
  audio_engine.init();
  ASGE::FILEIO::File bg_audio_file;
  if (bg_audio_file.open("/data/audio/cyberpunk.mp3"))
  {
    auto buffer = bg_audio_file.read();
    auto length = static_cast<unsigned int>(buffer.length);
    title_bg_audio.loadMem(buffer.as_unsigned_char(), length, false, false);
    title_bg_audio.setLooping(true);
    audio_engine.play(title_bg_audio);
  }
}
void TitleState::init()
{
  // renderer->setClearColour(ASGE::COLOURS::DARKOLIVEGREEN);
  initMenuButtons(_renderer);
  initAudio();
  initialized = true;
}

void TitleState::menuGraphicsAnimation()
{
  bg_moving.sprite()->getSprite()->xPos(Interpolation::lerp(
    bg_moving_anim_start, bg_moving_anim_start - 5696, bg_moving_anim_frames, bg_moving_anim_step));
  if (bg_moving_anim_step < bg_moving_anim_frames)
  {
    bg_moving_anim_step++;
  }
  else
  {
    bg_moving_anim_step = 0;
  }

  title_card.sprite()->getSprite()->yPos(Interpolation::invertCurve(
    title_card_anim_start, title_card_anim_start + 20, anim_frames, anim_step));
}

void TitleState::buttonsAnimation()
{
  for (int i = 0; i < amount_menu_buttons; i++)
  {
    menu_buttons[i].sprite()->getSprite()->yPos(Interpolation::invertCurve(
      menu_button_anim_start[i], menu_button_anim_start[i] + 20, anim_frames, anim_step));
  }
  if (anim_step < anim_frames)
  {
    anim_step++;
  }
  else
  {
    anim_step = 0;
  }
}

void TitleState::gamepadHandler()
{
  auto gamepad_one = _inputs->getGamePad();
  if (gamepad_one.is_connected)
  {
    if (gamepad_one.buttons[0] != 0U && !gamepad_one_button_press)
    {
      if (menu_buttons[0].getIsActive())
      {
        menu_buttons[0].setIsActive(false);
        menu_buttons[0].setState(Buttons::READY_INDENT);
      }
      else
      {
        menu_buttons[0].setIsActive(true);
        menu_buttons[0].setState(Buttons::NOT_READY_INDENT);
      }
      gamepad_one_button_press = true;
    }
    else if (gamepad_one.buttons[0] == 0U)
    {
      if (menu_buttons[0].getIsActive())
      {
        menu_buttons[0].setState(Buttons::READY);
      }
      else
      {
        menu_buttons[0].setState(Buttons::NOT_READY);
      }
      gamepad_one_button_press = false;
    }
  }

  auto gamepad_two = _inputs->getGamePad(1);
  if (gamepad_two.is_connected)
  {
    if (gamepad_two.buttons[0] != 0U && !gamepad_two_button_press)
    {
      if (menu_buttons[1].getIsActive())
      {
        menu_buttons[1].setIsActive(false);
        menu_buttons[1].setState(Buttons::READY_INDENT);
      }
      else
      {
        menu_buttons[1].setIsActive(true);
        menu_buttons[1].setState(Buttons::NOT_READY_INDENT);
      }
      gamepad_two_button_press = true;
    }
    else if (gamepad_two.buttons[0] == 0U)
    {
      if (menu_buttons[1].getIsActive())
      {
        menu_buttons[1].setState(Buttons::READY);
      }
      else
      {
        menu_buttons[1].setState(Buttons::NOT_READY);
      }
      gamepad_two_button_press = false;
    }
  }
}
