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

    return 0;
}
