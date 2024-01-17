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
vector<vector<int>> readGraph(string path){
    // Create and open a stream to read the file contents by giving the path to the file
    ifstream file(path);
    int num_vertices = 0;
    vector<vector<int>> adjacency_matrix;
    
    if(file.is_open()) {
        // Get the number of vertices in the graph in the first line
        file >> num_vertices;
        
        // Read the adjacency matrix
        int aux = 0;
        for(int i = 0 ; i < num_vertices ; i++){
            adjacency_matrix.push_back(vector<int>());
            for(int j = 0 ; j < num_vertices ; j++){
                file >> aux;
                adjacency_matrix.back().push_back(aux);
            }
        }
        
        file.close();
    }else {
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
vector<int> evaluateDegrees(const vector<vector<int>> &adjacency_matrix){
    vector<int> degrees(adjacency_matrix.size(),0);

    for(int i = 0; i < adjacency_matrix.size() ; i++) {
        // int degree = 0;
        for (uint j = 0; j < adjacency_matrix.size() ; j++) {
            if(adjacency_matrix[i][j] > 0)
                // degree++;
                degrees[i]++;
        }
        // degrees.push_back(degree);
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
void saveDegrees(const vector<int> &degrees, string path){
    ofstream file(path);

    if(file.is_open()){
        for(int i = 0 ; i < degrees.size(); i++) {
            file << "Vertex " << i + 1 << " degree: " << degrees[i] << endl;
        }
        file.close();
        cout << "Degrees saved to " << path << endl;
    }else {
        cerr << "Unable to create file: " << path << endl;
    }
}

/***********************************************************************************
*  MAIN
***********************************************************************************/
int main(){
    string  input_file_path = "input/graph.txt"
           ,output_file_path = "output/degrees.txt";

    // Read the graph
    vector<vector<int>> adjacency_matrix = readGraph(input_file_path);

    // Print the graph
    cout << "The graph read has " << adjacency_matrix.size() << " vertices and the following arcs:" << endl;
    for(vector<int> row : adjacency_matrix){
        for(int element : row){
            cout << setw(4) << element << " ";
        }
        cout << endl;
    }

    // Evaluate the degree of each vertex and save the results in a file
    vector<int> degrees = evaluateDegrees(adjacency_matrix);

    // Save the degrees to a file
    saveDegrees(degrees, output_file_path);

    return 0;
}
