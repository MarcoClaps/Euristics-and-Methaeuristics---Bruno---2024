#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

/***********************************************************************************
 *  readGraph
 *
 *  @brief Read the graph represented in the given file
 *
 *  @param path (string): the path to the given file
 *
 *  @return [vector<vector<int>>] The graph represented as an adjacency matrix
 ***********************************************************************************/
vector<vector<int>> readGraph(string path)
{
    // Create and open a stream to read the file contents by giving the path to the file
    ifstream file(path);
    int num_vertices = 0;
    vector<vector<int>> adjacency_matrix;

    if (file.is_open())
    {
        // Get the number of vertices in the graph in the first line
        file >> num_vertices;

        // Read the adjacency matrix
        int aux = 0;
        for (int i = 0; i < num_vertices; i++)
        {
            adjacency_matrix.push_back(vector<int>());
            for (int j = 0; j < num_vertices; j++)
            {
                file >> aux;
                adjacency_matrix.back().push_back(aux);
            }
        }

        file.close();
    }
    else
    {
        cerr << "Unable to open file: " << path << std::endl;
    }

    return adjacency_matrix;
}

/***********************************************************************************
 *  evaluateDegrees
 *
 *  @brief Read the graph represented in the given file
 *
 *  @param adjacency_matrix (vector<vector<int>> &): the adjacency matrix
 *
 *  @return [vector<int>] An array containing the degree of each vertex
 ***********************************************************************************/
vector<int> evaluateDegrees(vector<vector<int>> &adjacency_matrix)
{
    vector<int> degrees;

    for (int i = 0; i < adjacency_matrix.size(); i++)
    {
        int degree = 0;
        for (int j = 0; j < adjacency_matrix.size(); j++)
        {
            if (adjacency_matrix[i][j] > 0)
                degree++;
        }
        degrees.push_back(degree);
    }

    return degrees;
}

/***********************************************************************************
 *  saveDegrees
 *
 *  @brief Save the degrees in a file
 *
 *  @param degrees (vector<int> &): an array containing the degree of each vertex
 *  @param path (string): the path to the output file
 *
 ***********************************************************************************/
void saveDegrees(vector<int> &degrees, string path, int &max_degree)
{
    ofstream file(path);

    if (file.is_open())
    {
        file << "Maximum degree: " << max_degree << endl;
        for (int i = 0; i < degrees.size(); i++)
        {
            file << "Vertex " << i + 1 << " degree: " << degrees[i] << endl;
        }
        file.close();
        cout << "Degrees saved to " << path << endl;
    }
    else
    {
        cerr << "Unable to create file: " << path << endl;
    }
}

/***********************************************************************************
 *  evaluateMaximumDegree
 *
 *  @brief Evaluate the maximum degree of the graph
 *
 *  @param degrees (vector<int> &): an array containing the degree of each vertex
 *  @param path (string): the path to the output file
 *
 ***********************************************************************************/

int evaluateMaximumDegree(vector<int> &degrees)
{
    int max_degree = 0;

    for (int i = 0; i < degrees.size(); i++)
    {
        if (degrees[i] > max_degree)
            max_degree = degrees[i];
    }

    return max_degree;
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

    // Read the graph
    vector<vector<int>> adjacency_matrix = readGraph(input_file_path);

    // Print the graph
    cout << "The graph read has " << adjacency_matrix.size() << " vertices and the following arcs:" << endl;
    for (vector<int> row : adjacency_matrix)
    {
        for (int element : row)
        {
            cout << setw(4) << element << " ";
        }
        cout << endl;
    }

    // Evaluate the degree of each vertex and save the results in a file
    vector<int> degrees = evaluateDegrees(adjacency_matrix);

    // Evaluate the maximum degree of the graph
    int max_degree = evaluateMaximumDegree(degrees);

    // Save the degrees to a file
    saveDegrees(degrees, output_file_path, max_degree);

    return 0;
}
