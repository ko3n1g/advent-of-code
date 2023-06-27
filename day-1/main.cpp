#include "include/elvetools.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main(int argc, char const *argv[]) {
  // Open file
  std::ifstream caloriesFile("data/challenge.txt");
  if (!caloriesFile.is_open()) {
    std::cout << "Failed to open file.";
    return 1;
  }

  // Convert buffer to string and close stream
  std::vector<std::string> caloriesVector =
      trimVectorEnd(convertStreamToVector(caloriesFile));

  // Parse file into 2D mapping of calories per Elve
  std::vector<std::vector<int>> caloriesPerElve = parseCalories(caloriesVector);

  // Create summary of caloriesPerElve and find Elve with the most calories
  std::vector<int> sumOfCaloriesPerElve = aggregateCalories(caloriesPerElve);

  // Argsort calories if Elves
  std::sort(sumOfCaloriesPerElve.begin(), sumOfCaloriesPerElve.end());

  // Print answer of part 1
  printf("Elve with the most calories has %d in total\n",
         sumOfCaloriesPerElve[sumOfCaloriesPerElve.size()-1]);

  // Print answer of part 2
  printf("Sum of top 3 elves is %d\n",
         std::accumulate(sumOfCaloriesPerElve.end() - 3,
                         sumOfCaloriesPerElve.end(), 0));

  return 0;
}