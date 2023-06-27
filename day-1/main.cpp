#include "include/elvetools.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
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

  // Get index of Elve with most calories
  int idxOfEleveWithMostCalories =
      std::distance(sumOfCaloriesPerElve.begin(),
                    std::max_element(sumOfCaloriesPerElve.begin(),
                                     sumOfCaloriesPerElve.end()));

  std::cout << printf("Elve number %d has the most calories (%d in total)\n",
                      idxOfEleveWithMostCalories + 1,
                      sumOfCaloriesPerElve[idxOfEleveWithMostCalories]);

  return 0;
}