#include "Interrogation.h"
#include <Engine/OGLGame.hpp>

void Interrogation::initTextInit(ASGE::Renderer* renderer)
{
  clocks.initQuestions(renderer);
  clocks.interrogation_question.setString("How many clocks were on the hospital floor you "
                                          "visited?");

  curtains.initQuestions(renderer);
  curtains.interrogation_question.setString("What colour were the bed curtains");

  bins.initQuestions(renderer);
  bins.interrogation_question.setString("What colour was the bin?");

  beds.initQuestions(renderer);
  beds.interrogation_question.setString("How many rooms had black beds?");

  computer_screens.initQuestions(renderer);
  computer_screens.interrogation_question.setString("What colour were the blank monitors?");

  bed_plant.initQuestions(renderer);
  bed_plant.interrogation_question.setString("Was there anything odd about the hospital floor?");

  toilet.initQuestions(renderer);
  toilet.interrogation_question.setString("What was at the front desk?");

  freezer.initQuestions(renderer);
  freezer.interrogation_question.setString("Did they have a freezer installed?");

  vending_machine.initQuestions(renderer);
  vending_machine.interrogation_question.setString("What colour was the vending machine at the "
                                                   "front desk?");

  fire_extinguisher.initQuestions(renderer);
  fire_extinguisher.interrogation_question.setString("What colour were the fire extinguishers?");

  game_over.setString("Game Over!!")
    .setPosition({ 100, 100 })
    .setScale(2)
    .setZOrder(3)
    .setFont(renderer->getDefaultFont());
}

void Interrogation::renderText(ASGE::Renderer* renderer)
{
  if (question_number == 0)
  {
    renderQuestion(clocks, renderer);
  }
  else if (question_number == 1)
  {
    renderQuestion(curtains, renderer);
  }
  else if (question_number == 2)
  {
    renderQuestion(bins, renderer);
  }
  else if (question_number == 3)
  {
    renderQuestion(beds, renderer);
  }

  else if (question_number == 4)
  {
    renderQuestion(computer_screens, renderer);
  }
  else if (question_number == 5)
  {
    renderQuestion(bed_plant, renderer);
  }

  else if (question_number == 6)
  {
    renderQuestion(toilet, renderer);
  }
  else if (question_number == 7)
  {
    renderQuestion(freezer, renderer);
  }

  else if (question_number == 8)
  {
    renderQuestion(vending_machine, renderer);
  }
  else if (question_number == 9)
  {
    renderQuestion(fire_extinguisher, renderer);
  }
  else
  {
    renderer->render(game_over);
  }
}

void Interrogation::setAnswers(
  int answer, const std::string& correct_answer_s, const std::string& wrong_answer_s,
  InterrogationQuestion& question)
{
  question.correct_answer = answer;
  if (answer == 1)
  {
    question.interrogation_answer_1.setString(correct_answer_s);
    question.interrogation_answer_2.setString(wrong_answer_s);
  }
  else
  {
    question.interrogation_answer_1.setString(wrong_answer_s);
    question.interrogation_answer_2.setString(correct_answer_s);
  }
}

void Interrogation::renderQuestion(InterrogationQuestion& question, ASGE::Renderer* renderer)
{
  renderer->render(question.interrogation_question);
  renderer->render(question.interrogation_answer_1);
  renderer->render(question.interrogation_answer_2);
}

void Interrogation::keyHandlerInterrogation()
{
  if (question_number == 0)
  {
    answerSelected(answer_option, clocks);
  }
  else if (question_number == 1)
  {
    answerSelected(answer_option, curtains);
  }
  else if (question_number == 2)
  {
    answerSelected(answer_option, bins);
  }
  else if (question_number == 3)
  {
    answerSelected(answer_option, beds);
  }

  else if (question_number == 4)
  {
    answerSelected(answer_option, computer_screens);
  }
  else if (question_number == 5)
  {
    answerSelected(answer_option, bed_plant);
  }
  else if (question_number == 6)
  {
    answerSelected(answer_option, toilet);
  }
  else if (question_number == 7)
  {
    answerSelected(answer_option, freezer);
  }

  else if (question_number == 8)
  {
    answerSelected(answer_option, vending_machine);
  }
  else if (question_number == 9)
  {
    answerSelected(answer_option, fire_extinguisher);
  }
  else
  {
    answer_option = 0;
  }
}

void Interrogation::answerRNG(const bool hospital_furniture[], int hospital_clocks)
{
  std::random_device rng_device;
  std::mt19937 rng_mt(rng_device());
  std::uniform_int_distribution<std::mt19937::result_type> rng_dist(1, 2);
  std::uniform_int_distribution<std::mt19937::result_type> rng_dist_c(2, 9);
  correct_answer = static_cast<int>(rng_dist(rng_mt));

  std::string correct_str;
  std::string wrong_str;

  int w_answer = static_cast<int>(
    hospital_clocks + ((pow(-1, 1 + static_cast<int>(rng_dist(rng_mt)))) *
                       (1 + static_cast<int>(rng_dist_c(rng_mt)))));
  if (w_answer < 0)
  {
    if ((w_answer * -1) != hospital_clocks)
    {
      w_answer = w_answer * -1;
    }
    else
    {
      w_answer = w_answer * -2;
    }
  }
  if (w_answer == hospital_clocks)
  {
    w_answer = w_answer + 1;
  }

  setAnswers(correct_answer, std::to_string(hospital_clocks), std::to_string(w_answer), clocks);

  if (hospital_furniture[2])
  {
    correct_str = "BLUE";
    wrong_str   = "WHITE";
  }
  else
  {
    wrong_str   = "BLUE";
    correct_str = "WHITE";
  }
  correct_answer = static_cast<int>(rng_dist(rng_mt));
  setAnswers(correct_answer, correct_str, wrong_str, curtains);

  if (hospital_furniture[4])
  {
    correct_str = "GREEN";
    wrong_str   = "GREY";
  }
  else
  {
    wrong_str   = "GREEN";
    correct_str = "GREY";
  }
  correct_answer = static_cast<int>(rng_dist(rng_mt));
  setAnswers(correct_answer, correct_str, wrong_str, bins);

  if (hospital_furniture[5])
  {
    correct_str = "2";
    wrong_str   = "0";
  }
  else
  {
    wrong_str   = "2";
    correct_str = "0";
  }
  correct_answer = static_cast<int>(rng_dist(rng_mt));
  setAnswers(correct_answer, correct_str, wrong_str, beds);

  if (hospital_furniture[6])
  {
    correct_str = "GREEN";
    wrong_str   = "BLUE";
  }
  else
  {
    wrong_str   = "GREEN";
    correct_str = "BLUE";
  }
  correct_answer = static_cast<int>(rng_dist(rng_mt));
  setAnswers(correct_answer, correct_str, wrong_str, computer_screens);

  if (hospital_furniture[1])
  {
    correct_str = "A plant in a hospital bed";
    wrong_str   = "A computer in a fridge";
  }
  else
  {
    if (hospital_furniture[0])
    {
      correct_str = "A toilet at a computer";
      wrong_str   = "No, nothing";
    }
    else
    {
      wrong_str   = "Fallen vending machine";
      correct_str = "No, nothing";
    }
  }
  correct_answer = static_cast<int>(rng_dist(rng_mt));
  setAnswers(correct_answer, correct_str, wrong_str, bed_plant);

  if (hospital_furniture[0])
  {
    correct_str = "A toilet";
    wrong_str   = "An office chair";
  }
  else
  {
    wrong_str   = "A toilet";
    correct_str = "An office chair";
  }
  correct_answer = static_cast<int>(rng_dist(rng_mt));
  setAnswers(correct_answer, correct_str, wrong_str, toilet);

  if (hospital_furniture[3])
  {
    correct_str = "YES";
    wrong_str   = "NO";
  }
  else
  {
    wrong_str   = "YES";
    correct_str = "NO";
  }
  correct_answer = static_cast<int>(rng_dist(rng_mt));
  setAnswers(correct_answer, correct_str, wrong_str, freezer);

  if (hospital_furniture[8])
  {
    correct_str = "PURPLE";
    wrong_str   = "RED";
  }
  else
  {
    wrong_str   = "PURPLE";
    correct_str = "RED";
  }
  correct_answer = static_cast<int>(rng_dist(rng_mt));
  setAnswers(correct_answer, correct_str, wrong_str, vending_machine);

  if (hospital_furniture[7])
  {
    correct_str = "BLUE";
    wrong_str   = "RED";
  }
  else
  {
    wrong_str   = "BLUE";
    correct_str = "RED";
  }
  correct_answer = static_cast<int>(rng_dist(rng_mt));
  setAnswers(correct_answer, correct_str, wrong_str, fire_extinguisher);
}

void Interrogation::answerSelected(int chosen_answer, InterrogationQuestion& question)
{
  if (chosen_answer == question.correct_answer)
  {
    correct_answer_given = true;
    question_number++;
  }
  else if (chosen_answer == 0)
  {
  }
  else
  {
    question_number++;
    correct_answer_given = false;
  }
}

int Interrogation::addScore(int score)
{
  return score + INTERROGATION_POINTS;
}
void Interrogation::setQuestionNumber(int x)
{
  question_number = x;
}
void Interrogation::setCorrectAnswer(int x)
{
  correct_answer = x;
}
void Interrogation::setAnswerOption(int x)
{
  answer_option = x;
}
int Interrogation::getQuestionNumber()
{
  return question_number;
}
int Interrogation::getCorrectAnswer()
{
  return correct_answer;
}
int Interrogation::getAnswerOption()
{
  return answer_option;
}
