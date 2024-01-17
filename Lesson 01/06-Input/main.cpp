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
vector<vector<int>> readGraph(const string &path){
    // Create and open a stream to read the file contents by giving the path to the file
    ifstream file(path);
    int num_vertices = 0;
    vector<vector<int>> adjacency_matrix;
    
    if(file.is_open()) {
        // Get the number of vertices in the graph in the first line
        file >> num_vertices;
        // Initialize the adjacency matrix with the wanted dimensions
        adjacency_matrix = vector<vector<int>>(num_vertices, vector<int>(num_vertices,0));
        
        // Read the adjacency matrix
        int aux = 0;
        for(int i = 0 ; i < num_vertices ; i++){
            // adjacency_matrix.push_back(vector<int>());
            // adjacency_matrix.back().reserve(num_vertices);
            for(int j = 0 ; j < num_vertices ; j++){
                file >> aux;
                // adjacency_matrix.back().push_back(aux);
                adjacency_matrix[i][j] = aux;
            }
        }
        
        file.close();
    }else {
        cerr << "Unable to open file: " << path << std::endl;
    }

    return adjacency_matrix;
}


/***********************************************************************************
*  MAIN
***********************************************************************************/
int main(){
    string file_path = "input/graph.txt";

    // Read the graph
    vector<vector<int>> adjacency_matrix = readGraph(file_path);

    // Print the graph
    cout << "The graph read has " << adjacency_matrix.size() << " vertices and the following arcs:" << endl;
    for(vector<int> row : adjacency_matrix){
        for(int element : row){
            cout << setw(4) << element << " ";
        }
        cout << endl;
    }

    return 0;
}
