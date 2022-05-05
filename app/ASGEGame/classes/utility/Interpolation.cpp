//
// Created by robbi on 17/04/2022.
//

#include "Interpolation.h"

/**
 * @brief Linear Interpolation
 *
 * Linear Interpolation between 2, 1D points.
 *
 * @param start
 * @param end
 * @param no_steps
 * @param current_step
 * @return
 */
float Interpolation::lerp(float start, float end, float no_steps, float current_step)
{
  float range      = end - start;
  float t          = current_step / no_steps;
  float lerp_value = range * t + start;

  return lerp_value;
}

/**
 * @brief Interpolation with Bezier
 *
 * Interpolation between 2, 1D points through a Bezier curve which has a gradual increase in
 * gradient
 *
 * @param start
 * @param end
 * @param no_steps
 * @param current_step
 * @return
 */
float Interpolation::easeIn(float start, float end, float no_steps, float current_step)
{
  float p1      = start;
  float p2      = lerp(start, end, no_steps, current_step);
  float p_final = lerp(p1, p2, no_steps, current_step);

  return p_final;
}

/**
 * @brief Interpolation with Bezier
 *
 * Interpolation between 2, 1D points through a Bezier curve which has a gradual decrease in
 * gradient
 *
 * @param start
 * @param end
 * @param no_steps
 * @param current_step
 * @return
 */
float Interpolation::easeOut(float start, float end, float no_steps, float current_step)
{
  float p1      = lerp(start, end, no_steps, current_step);
  float p2      = end;
  float p_final = lerp(p1, p2, no_steps, current_step);

  return p_final;
}

/**
 * @brief Interpolation with Bezier
 *
 * Interpolation between 2, 1D points that cross halfway through the interpolation.
 *
 * @param start
 * @param end
 * @param no_steps
 * @param current_step
 * @return
 */
float Interpolation::invertCurve(float start, float end, float no_steps, float current_step)
{
  float p1      = lerp(start, end, no_steps, current_step);
  float p2      = lerp(end, start, no_steps, current_step);
  float p_final = lerp(p1, p2, no_steps, current_step);

  return p_final;
}

/**
 * @brief Interpolation with Bezier
 *
 * Interpolation between 2, 1D points
 *
 * @param start
 * @param end
 * @param no_steps
 * @param current_step
 * @return
 */
float Interpolation::sCurve(float start, float end, float no_steps, float current_step)
{
  float p1      = lerp(start, end, no_steps, current_step);
  float p2      = lerp(end, start, no_steps, current_step);
  float p_final = 0;

  if (current_step <= no_steps / 2)
  {
    p_final = lerp(p1, p2, no_steps, current_step);
  }
  else
  {
    p_final = lerp(p2, p1, no_steps, current_step);
  }

  return p_final;
}
