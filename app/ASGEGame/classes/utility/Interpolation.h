//
// Created by robbi on 17/04/2022.
//

#ifndef ASGEGAME_INTERPOLATION_H
#define ASGEGAME_INTERPOLATION_H

#pragma once

struct Interpolation
{
  static float lerp(float start, float end, float no_steps, float current_step);
  static float easeIn(float start, float end, float no_steps, float current_step);
  static float easeOut(float start, float end, float no_steps, float current_step);
  static float invertCurve(float start, float end, float no_steps, float current_step);
  static float sCurve(float start, float end, float no_steps, float current_step);
};

#endif // ASGEGAME_INTERPOLATION_H