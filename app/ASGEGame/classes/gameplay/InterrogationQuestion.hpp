//
// Created by bhe06 on 18/04/2022.
//
#pragma once

#include <Engine/Renderer.hpp>
#include <Engine/Text.hpp>
struct InterrogationQuestion
{
  ASGE::Text interrogation_question;
  ASGE::Text interrogation_answer_1;
  ASGE::Text interrogation_answer_2;

  int correct_answer = 0;

  void initQuestions(ASGE::Renderer* renderer);
};