#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <list>

using namespace std;

/***********************************************************************************
 *  readFile
 *
 *  @brief Read a puzzle file
 *
 *  @param path (string): the path to the given file
 *
 *  @return [vector<string>] The lines of the file
 ***********************************************************************************/
vector<string> readFile(string path)
{
    // Create and open a stream to read the file contents by giving the path to the file
    ifstream file(path);
    vector<string> lines;

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
    }
    else
    {
        cerr << "Unable to open file: " << path << std::endl;
    }

    return lines;
}

/***********************************************************************************
 * writeToFile
 *
 * @brief Write the result to the output file
 *
 * @param path (string): the path to the given file
 * @param resultSum (int): the sum of the numbers
 *
 * @return [void]
 ***********************************************************************************/

void writeToFile(const string &path, const int &resultSum)
{
    ofstream file(path);

    if (file.is_open())
    {
        // print the result to the file
        file << "Final sum: " << resultSum << endl;
    }
    else
    {
        cerr << "Unable to create file: " << path << endl;
    }
}

/***********************************************************************************
 *  sumAlongVector
 *
 * @brief Sum the numbers along a vector
 *
 * @param numbers (vector<int>): the numbers to sum
 *
 * @return [int] The sum of the numbers
 *
 ***********************************************************************************/
int sumAlongVector(const vector<int> &numbers)
{
    int sum = 0;
    for (int i = 0; i < numbers.size(); i++)
    {
        // the sum adds 2 pow (numbers[i]-1)
        sum += putw(2, numbers[i] - 1);
    }
    return sum;
}

/***********************************************************************************
 *  splitStringToInt
 *
 * @brief Split a string to a list of int
 *
 * @param str (string): the string to split
 * @param delimiter (char): the delimiter to split the string
 *
 * @return [list<int>] The list of int
 *
 ***********************************************************************************/
list<int> splitStringToInt(const string &str, const char &delimiter)
{
    list<int> result;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter))
    {
        result.push_back(stoi(token));
    }
    return result;
}
/***********************************************************************************
 *  checkEqualities
 *
 * @brief Check if the numbers are equal
 *
 * @param lines (vector<string>): the lines of number to check
 *
 * @return vector<int> The equal numbers for each line read
 *
 ***********************************************************************************/
vector<int> checkEqualities(const vector<string> &lines)
{
    vector<int> result = vector<int>(lines.size());
    // iterate over the lines
    for (int i = 0; i < lines.size(); i++)
    {
        // Replace in the line "Card (i+1): " by nothing
        lines[i] = rename(lines[i], "Card " + to_string(i + 1) + ": ", "");
        // split the line
        vector<string> line_v1 = split(lines[i], '|');
        list<int> lineToCheck = splitStringToInt(line_v1[0], ' ');
        list<int> lineToCheckOn = splitStringToInt(line_v1[1], ' ');

        countChecks = 0;
        // iterate over lineToCheck
        for (int j = 0; j < lineToCheck.size(); j++)
        {
            // iterate over lineToCheckOn
            for (int k = 0; k < lineToCheckOn.size(); k++)
            {
                // if the numbers are equal
                if (lineToCheck[j] == lineToCheckOn[k])
                {
                    // increase the countChecks
                    countChecks++;
                    // delete the number from lineToCheckOn
                    lineToCheckOn.erase(lineToCheckOn.begin() + k);
                }
            }
        }
        // add the countChecks to the result
        result[i] = countChecks;
    }
}
/***********************************************************************************
 *  MAIN
 ***********************************************************************************/
int main(int argc, char *argv[])
{

    string input_file_path, output_file_path;

    // Parse command line arguments
    for (int i = 1; i < argc; ++i)
    {
        // Input file path
        if (string(argv[i]) == "-i" && i + 1 < argc)
        {
            input_file_path = argv[i + 1];
        }
        // Output file path
        else if (string(argv[i]) == "-o" && i + 1 < argc)
        {
            output_file_path = argv[i + 1];
        }
    }

    // Check if the file names were given
    if (input_file_path.empty() || output_file_path.empty())
    {
        cerr << "Usage: " << argv[0] << " -i <input_filename> -o <output_filename>" << endl;
        return 1;
    }

    // Read the file
    vector<string> lines = readFile(input_file_path);

    // do the checks
    vector<int> resultVector = checkEqualities(lines);

    // sum the result
    int result = sumAlongVector(resultVector);

    // Write the result to the output file
    writeToFile(output_file_path, result);

    return 0;
}
