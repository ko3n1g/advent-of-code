#include "include/gametools.h"

int main(int argc, char const *argv[]) {

  // Open file
  std::ifstream gamePlay1("data/challenge.txt");
  if (!gamePlay1.is_open()) {
    std::cout << "Failed to open file.";
    return 1;
  }

  // Display result of part-1
  part1(gamePlay1);

  // Open file
  std::ifstream gamePlay2("data/challenge.txt");
  if (!gamePlay2.is_open()) {
    std::cout << "Failed to open file.";
    return 1;
  }

  // Display result of part-2
  part2(gamePlay2);

  return 0;
}
