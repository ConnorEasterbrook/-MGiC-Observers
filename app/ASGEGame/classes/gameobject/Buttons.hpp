//
// Created by robbi on 03/02/2022.
//

#ifndef ASGENETGAME_BUTTONS_HPP
#define ASGENETGAME_BUTTONS_HPP

#include "GameObject.h"

class Buttons : public GameObject
{
 public:
  Buttons()           = default;
  ~Buttons() override = default;

  void setIsActive(bool change_activity);
  [[nodiscard]] bool getIsActive() const;
  void setState(int state);
  [[nodiscard]] int getState() const;
  void setSpriteSheetWidth(float x);
  [[nodiscard]] float getSpriteSheetWidth() const;
  void setSpriteSheetHeight(float y);
  [[nodiscard]] float getSpriteSheetHeight() const;
  void setSpriteScaler(float scale);
  [[nodiscard]] float getSpriteScaler() const;

  void goRender(ASGE::Renderer* renderer, float z_order) const override;
  bool addSpriteComponent(
    const std::string& texture_file_path, std::unique_ptr<SpriteComponent> unique_sc,
    ASGE::Renderer* renderer, int z_order) override;
  bool clickCollision(ASGE::SharedEventData data) override;

  enum ButtonState
  {
    NOT_READY,
    NOT_READY_INDENT,
    READY,
    READY_INDENT
  };

 private:
  bool is_active            = false;
  int current_state         = NOT_READY;
  float sprite_sheet_width  = 57;
  float sprite_sheet_height = 18;
  float sprite_scaler       = 4;
  float x_bound             = 0;
  float y_bound             = 18;
  //  float active_x_bound      = 0;
  //  float active_y_bound      = 0;

  float not_ready_x     = 0;
  float not_ready_y     = 0;
  float not_ready_ind_x = 0;
  float not_ready_ind_y = 18;
  float ready_x         = 0;
  float ready_y         = 36;
  float ready_ind_x     = 0;
  float ready_ind_y     = 54;
};

#endif // ASGENETGAME_BUTTONS_HPP
