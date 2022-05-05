#ifndef ASGEGAME_INTERROGATION_H
#define ASGEGAME_INTERROGATION_H

#include "InterrogationQuestion.hpp"
#include "random"
#include <Engine/Renderer.hpp>

class Interrogation
{
 public:
  Interrogation()  = default;
  ~Interrogation() = default;

  void initTextInit(ASGE::Renderer* renderer);
  void renderText(ASGE::Renderer* renderer);
  void renderQuestion(InterrogationQuestion& question, ASGE::Renderer* renderer);
  void keyHandlerInterrogation();
  void setAnswers(
    int answer, const std::string& correct_answer_s, const std::string& wrong_answer_s,
    InterrogationQuestion& question);
  void answerRNG(const bool hospital_furniture[], int hospital_clocks);
  void answerSelected(int chosen_answer, InterrogationQuestion& question);
  void setQuestionNumber(int x);
  void setCorrectAnswer(int x);
  void setAnswerOption(int x);
  int getQuestionNumber();
  int getCorrectAnswer();
  int getAnswerOption();
  int addScore(int score);
  bool correct_answer_given = false;
  InterrogationQuestion clocks;
  InterrogationQuestion curtains;
  InterrogationQuestion bins;
  InterrogationQuestion beds;
  InterrogationQuestion computer_screens;
  InterrogationQuestion bed_plant;
  InterrogationQuestion toilet;
  InterrogationQuestion freezer;
  InterrogationQuestion vending_machine;
  InterrogationQuestion fire_extinguisher;
  ASGE::Text game_over;

 private:
  const int INTERROGATION_POINTS = 40000;

  int question_number = 0;
  int correct_answer  = 0;
  int answer_option   = 0;
};

#endif // ASGEGAME_INTERROGATION_H
