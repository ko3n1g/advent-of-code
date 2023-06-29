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


int main(int argc, char const *argv[]) {

  enum Symbol { Rock, Paper, Scissor };
  Symbol rock = Rock;
  Symbol paper = Paper;
  Symbol scissor = Scissor;

  std::map<Symbol, Symbol> beats{{rock, scissor}, {scissor, paper}, {paper, rock}};
  std::map<std::string, Symbol> strategyToSymbol{{"A", rock}, {"B", paper}, {"C", scissor},
                                             {"X", rock}, {"Y", paper}, {"Z", scissor}};
  std::map<Symbol, int> symbolToPoint{{rock, 1},{paper, 2}, {scissor, 3}};

  // Open file
  std::ifstream gamePlay("data/challenge.txt");
  if (!gamePlay.is_open()) {
    std::cout << "Failed to open file.";
    return 1;
  }

  std::string currentLine;
  std::string delimiter = " ";
  int totalScore = 0;
  while (getline(gamePlay, currentLine)) {
    Symbol opponent = strategyToSymbol[currentLine.substr(0, currentLine.find(delimiter))];
    Symbol ours =
        strategyToSymbol[currentLine.substr(currentLine.find(delimiter) + 1, currentLine.length())];

    int score = symbolToPoint[ours] + (beats[opponent] == ours ? 0 : (opponent == ours ? 3 : 6));
    totalScore += score;
    std::cout << std::to_string(opponent) + ":" + std::to_string(ours) + "=" + std::to_string(score) + "\n";
  };

  printf("Total score: %d\n", totalScore);

  return 0;
}
