/**
 * Converts a stream to a vector, and closes the vector afterwards by default.
 *
 * @param: stream Stream to convert
 * @param: close Whether to close the stream afterwards. Defaults to true
 */
std::vector<std::string> convertStreamToVector(std::ifstream &stream, bool close = true)
{
    std::vector<std::string> vector;
    std::string currentLine;
    while (getline(stream, currentLine))
    {
        vector.push_back(currentLine);
    };

    if (close)
    {
        stream.close();
    }

    return vector;
}

/**
 * Guarantees that the vector will have only a single final empty item.
 *
 * @param vector Vector to trim. Will have a single empty final item.
 */
std::vector<std::string> trimVectorEnd(std::vector<std::string> vector)
{
    for (size_t i = vector.size() - 1; i >= 0; i--)
    {
        // If the line is non-empty, we are done
        if (vector[i].length())
        {
            break;
        }

        vector.pop_back();
    }
    vector.push_back("");
    return vector;
}

/**
 * Parses a vector of strings to a vector of integers. Assumes that all strings can
 * in fact be parsed to integers and will crash if that is not the case.
 *
 * @param vectorOfStringCalories Vector of strings to be casted to vector of ints.
 */
std::vector<std::vector<int>> parseCalories(std::vector<std::string> vectorOfStringCalories)
{
    std::vector<std::vector<int>> vectorOfIntCalories;
    std::string line;
    std::vector<int> intCalories;
    for (auto item : vectorOfStringCalories)
    {
        if (!item.length())
        {
            vectorOfIntCalories.push_back(intCalories);
            intCalories.clear();
            continue;
        }

        intCalories.push_back(std::stoi(item));
    }

    return vectorOfIntCalories;
}

/**
 * Aggregates a 2D vector of calories into a 1D vector by applying a sum row-wise.
 *
 * @param vectorOfCaloriesPerElve 2D vector to aggregate.
 */
std::vector<int> aggregateCalories(std::vector<std::vector<int>> vectorOfCaloriesPerElve)
{
    std::vector<int> sumOfCaloriesPerElve;
    std::vector<int> calories;
    for (auto vectorOfCalories : vectorOfCaloriesPerElve)
    {
        int sumOfCalories = 0;
        for (auto calorie : vectorOfCalories)
        {
            sumOfCalories += calorie;
        }
        sumOfCaloriesPerElve.push_back(sumOfCalories);
    }
    return sumOfCaloriesPerElve;
}