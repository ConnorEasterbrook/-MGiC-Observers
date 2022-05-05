//
// Created by bhe06 on 18/04/2022.
//

#include "InterrogationQuestion.hpp"
void InterrogationQuestion::initQuestions(ASGE::Renderer* renderer)
{
  interrogation_question.setFont(renderer->getDefaultFont())
    .setPosition({ 100, 100 })
    .setColour(ASGE::COLOURS::BLACK)
    .setScale(.5F)
    .setZOrder(1);
  interrogation_answer_1.setFont(renderer->getDefaultFont())
    .setPosition({ 100, 300 })
    .setColour(ASGE::COLOURS::BLACK)
    .setScale(.5F)
    .setZOrder(1);
  interrogation_answer_2.setFont(renderer->getDefaultFont())
    .setPosition({ 800, 300 })
    .setColour(ASGE::COLOURS::BLACK)
    .setScale(.5F)
    .setZOrder(1);
}
