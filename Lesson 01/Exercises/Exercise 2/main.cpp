#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

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
 * evaluateSum
 *
 * @brief For each line of the file, get out the first and last number, then use them to compose a two digit number. In the end sum all the numbers.
 *
 * @param lines (vector<string> &): the lines of the file
 *
 * @return [int] The sum of the numbers
 *
 ***********************************************************************************/

int evaluateSum(const vector<string> &lines)
{
    int sum = 0;
    vector<int> numbers;
    // reserve the space for the vector
    numbers.reserve(lines.size());
    for (int i = 0; i < lines.size(); ++i)
    {
        // declare an empty string to store the numbers
        string tempLine;
        for (int j = 0; j < lines[i].size(); ++j)
        {
            if (isdigit(lines[i][j]))
            {
                tempLine.push_back(lines[i][j]);
                break;
            }
        }
        for (int k = lines[i].size(); k >= 0; --k)
        {
            if (isdigit(lines[i][k]))
            {
                tempLine.push_back(lines[i][k]);
                break;
            }
        }
        
    // do the conversion of tempLine to int, then add to the vector
        int tempNum = stoi(tempLine);
        numbers.push_back(tempNum);
    }
    for (int i = 0; i < numbers.size(); ++i)
    {
        sum += numbers[i];
        // cout << i << " -> " << numbers[i] << endl;
    }

    return sum;
}

/***********************************************************************************
 * evaluateSumUpgraded
 * 
 * @brief For each line of the file, get out the first and last number (they can be both digit or words), then use them to compose a two digit number. In the end sum all the numbers.
 * 
 * @param lines (vector<string> &): the lines of the file
 * 
 * @return [int] The sum of the numbers
 * 
 ***********************************************************************************/

int evaluateSumUpgraded(const vector<string> &lines)
{
    // TODO: implement this function
    int sum = 0;
    vector<int> numbers;
    // reserve the space for the vector
    numbers.reserve(lines.size());
    for (int i = 0; i < lines.size(); ++i)
    {
        // declare an empty string to store the numbers
        string tempLine;
        bool lastDigitFound = false;
        for (int j = 0; j < lines[i].size(); ++j)
        {
            if (isdigit(lines[i][j]))
            {
                tempLine.push_back(lines[i][j]);
                break;
            }
        }
        for (int k = lines[i].size(); k >= 0; --k)
        {
            if (isdigit(lines[i][k]))
            {
                tempLine.push_back(lines[i][k]);
                break;
            }
        }

        // do the conversion of tempLine to int, then add to the vector
        int tempNum = stoi(tempLine);
        numbers.push_back(tempNum);
    }
    for (int i = 0; i < numbers.size(); ++i)
    {
        sum += numbers[i];
        // cout << i << " -> " << numbers[i] << endl;
    }

    return sum;
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

    // Evaluate the sum
    int resultSum = evaluateSum(lines);

    // Write the result to the output file
    writeToFile(output_file_path, resultSum);

    return 0;
}
