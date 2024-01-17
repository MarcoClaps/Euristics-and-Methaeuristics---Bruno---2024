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
 * ReadThreeLines
 *
 * @brief read lines three by three and evaluate
 *
 * @param grid (vector<vector<char>>): the grid to evaluate
 *
 * @return [int] The sum of the numbers
 ***********************************************************************************/

int ReadThreeLines(const vector<string> &lines)
{
    int sum = 0;
    vector<int> numbers;

    // iterate over the grid
    for (int i = 0; i < lines.size(); ++i)
    {
        string tempString;

        for (int j = 0; j < lines[i].size(); ++j)
        {
            if (isdigit(lines[i][j]))
            {
            }
        }
    }

    // sum the numbers
    for (int i = 0; i < numbers.size(); ++i)
    {
        sum += numbers[i];
    }

    return sum;
}

/***********************************************************************************
 *  searchAround
 *
 *  @brief Search around the given position for symbols
 *
 * @param positions (vector<vector<int>>): the positions to evaluate
 *
 * @return bool
 ***********************************************************************************/

bool searchAround(const vector<vector<int>> &positions)
{
    bool found = false;

    for (int i = 0; i < positions.size(); ++i)
    {
        int x = positions[i][0];
        int y = positions[i][1];

        // check if the position is valid
        if (x >= 0 && x < grid.size() && y >= 0 && y < grid[x].size())
        {
            // check if the position is a symbol
            if ((grid[x][y] >= 33 && grid[x][y] <= 45) ||
                grid[x][y] == 47 ||
                (grid[x][y] >= 58 && grid[x][y] <= 64))
            {
                cout << "Found a symbol at: " << x << "-" << y << " " << grid[x][y] << endl;
                found = true;
                break;
            }
        }
    }

    return found;
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

    // Evaluate the grid
    int resultSum = ReadThreeLines(lines);

    return 0;
}
