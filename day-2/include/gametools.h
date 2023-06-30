#include <fstream>
#include <iostream>
#include <map>
#include <string>
/**
 * We need a mapping to decode the strategy:
 * A -> Rock
 * B -> Paper
 * C -> Scissors
 * X -> Rock
 * Y -> Pape
 * Z -> Scissors
 *
 * Rock -> 1
 * Paper -> 2
 * Scissors -> 3
 *
 * 0 -> Scissors
 * 1 -> Rock
 * 2 -> Paper
 * 3 -> Scissors
 * 4 -> Rock
 * 5 -> Paper
 *
 * This we can use to transform a string "<P1> <P2>" into two variables P1 =
 * mapping[<P1>], and P2 = mapping[<P2>]
 *
 * score = P2 + P1 >= P2 ? 0 : (P1 == P2) ? 3 : 6
 *
 */

enum Symbol { Rock, Paper, Scissor };
Symbol rock = Rock;
Symbol paper = Paper;
Symbol scissor = Scissor;

std::map<Symbol, int> symbolToPoint{{rock, 1}, {paper, 2}, {scissor, 3}};
std::map<Symbol, Symbol> beats{
    {rock, scissor}, {scissor, paper}, {paper, rock}};

void part1(std::ifstream &gamePlay) {
  std::map<std::string, Symbol> strategyToSymbol{
      {"A", rock}, {"B", paper}, {"C", scissor},
      {"X", rock}, {"Y", paper}, {"Z", scissor}};

  std::string currentLine;
  std::string delimiter = " ";
  int totalScore = 0;
  while (getline(gamePlay, currentLine)) {
    Symbol opponent =
        strategyToSymbol[currentLine.substr(0, currentLine.find(delimiter))];
    Symbol ours = strategyToSymbol[currentLine.substr(
        currentLine.find(delimiter) + 1, currentLine.length())];

    int score = symbolToPoint[ours] +
                (beats[opponent] == ours ? 0 : (opponent == ours ? 3 : 6));
    totalScore += score;
    std::cout << std::to_string(opponent) + ":" + std::to_string(ours) + "=" +
                     std::to_string(score) + "\n";
  };

  printf("Total score: %d\n", totalScore);
}

void part2(std::ifstream &gamePlay) {
  enum Outcome { Win, Draw, Loose };
  Outcome win = Win;
  Outcome draw = Draw;
  Outcome loose = loose;

  std::map<std::string, Symbol> strategyToSymbol{
      {"A", rock}, {"B", paper}, {"C", scissor}};
  std::map<std::string, Outcome> letterToOutcome{
      {"X", loose}, {"Y", draw}, {"Z", win}};
  std::map<Symbol, Symbol> looses;
  for (std::map<Symbol, Symbol>::iterator i = beats.begin(); i != beats.end();
       ++i) {
    looses[i->second] = i->first;
  }

  std::string currentLine;
  std::string delimiter = " ";
  int totalScore = 0;
  while (getline(gamePlay, currentLine)) {
    Symbol opponent =
        strategyToSymbol[currentLine.substr(0, currentLine.find(delimiter))];
    Outcome gameOutcome = letterToOutcome[currentLine.substr(
        currentLine.find(delimiter) + 1, currentLine.length())];

    Symbol ours = gameOutcome == loose
                      ? beats[opponent]
                      : (gameOutcome == draw ? opponent : looses[opponent]);

    int score = symbolToPoint[ours] +
                (beats[opponent] == ours ? 0 : (opponent == ours ? 3 : 6));
    totalScore += score;
    std::cout << std::to_string(opponent) + ":" + std::to_string(ours) + "=" +
                     std::to_string(score) + "\n";
  };

  printf("Total score: %d\n", totalScore);
}