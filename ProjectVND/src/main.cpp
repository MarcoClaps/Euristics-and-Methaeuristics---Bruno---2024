#include "../include/instance.hpp"
#include "../include/vnd.hpp"
#include "../include/solution.hpp"
#include <iostream>
#include <float.h>
#include <chrono>
#include <math.h>

using namespace std;
using namespace std::chrono;

/***********************************************************************************
 * @brief: greedy construction of the initial solution
 *
 * @param instance: instance of the problem
 *
 * @return solution: initial solution
 ***********************************************************************************/
Solution greedyConstruction(Instance &instance)
{
    Solution solution;
    const vector<vector<double>> &distMatrix = instance.getDistanceMatrix();

    int n_vertices = instance.getDistanceMatrix().size();
    vector<bool> visited = vector<bool>(n_vertices, false);
    vector<int> route = vector<int>(n_vertices + 1);
    route[0] = 0;
    visited[0] = true;

    double solutionValue = 0;
    int count = 0;

    for (int i = 0; i < n_vertices; i++)
    {
        int aux = -1;
        double dist = DBL_MAX;

        for (int j = 0; j < n_vertices; j++)
        {
            if (route[i] != j && !visited[j])
            {
                if (instance.getDistanceMatrix()[route[i]][j] < dist)
                {
                    aux = j;
                    dist = instance.getDistanceMatrix()[route[i]][j];
                }
            }
        }
        if (aux != -1)
        {
            route[i + 1] = aux;
            solutionValue += dist;
            visited[aux] = true;
        }
    }
    route[n_vertices] = 0;
    solutionValue += instance.getDistanceMatrix()[route[n_vertices - 1]][route[n_vertices]];

    solution.setRoute(route);
    solution.setSolutionValue(solutionValue);

    return solution;
}

/***********************************************************************************
 * @brief: export the results to a txt file. Greedy and VND execution time and solution value
 *
 * @param path: path to the txt file
 * @param solution: solution
 * @param routeGre: route of the greedy construction
 * @param executionTimeGreedy: execution time of the greedy construction
 * @param solutionValueGreedy: solution value of the greedy construction
 * @param routeVND: route of the VND
 * @param executionTimeVND: execution time of the VND
 * @param solutionValueVND: solution value of the VND
 *
 * @return void
 ***********************************************************************************/
void exportResults(string &path, Solution &solution, vector<int> &routeGre, int &executionTimeGreedy, int &solutionValueGreedy, vector<int> &routeVND, int &executionTimeVND, int &solutionValueVND)
{
    ofstream file(path);
    // gather the size of the route
    int n = routeGre.size();
    // Do the square root (douple) the ceil (int)
    int breakline = ceil(sqrt(n));
    // print the breakline value
    cout << "Breakline with value: " << breakline << endl;

    if (file.is_open())
    {
        file << "##### Initial Solution #####" << endl;
        file << "Route: ";
        int printed = 0;
        for (int i = 0; i < routeGre.size(); i++)
        {
            file << routeGre[i] << " ";
            printed++;
            if (printed == breakline)
            {
                file << "\n";
                printed = 0;
            }
        }
        file << "\nSolution Value: " << solutionValueGreedy << endl;
        file << "\nExecution time: " << executionTimeGreedy << "ms\n"
             << endl;
        file << "############################\n"
             << endl;
        file << "###### Best Solution #######" << endl;
        file << "Route: ";
        printed = 0;
        for (int i = 0; i < routeVND.size(); i++)
        {
            file << routeVND[i] << " ";
            printed++;
            if (printed == breakline)
            {
                file << endl;
                printed = 0;
            }
        }
        file << "\nSolution Value: " << solutionValueVND << endl;
        file << "\nExecution time: " << executionTimeVND << "ms\n"
             << endl;
        file << "############################" << endl;
        file.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
}

/***********************************************************************************
 *  MAIN
 ***********************************************************************************/
int main(int argc, char **argv)
{
    string pathInstance;
    int iterations;
    VND solver;

    if (argc < 2)
    {
        cout << "Few arguments! The command is: ./vnd [Instance]" << endl;
        exit(1);
    }
    else if (argc > 2)
    {
        cout << "Many arguments! The correct command is: ./vnd [Instance]" << endl;
        exit(1);
    }

    pathInstance = string(argv[1]);

    // read the instance
    Instance instance(pathInstance);
    instance.readMatrix();
    // instance.printMatrix();

    // time start greedy
    auto startGreedy = high_resolution_clock::now();

    // procedure
    Solution solution = greedyConstruction(instance);
    vector<int> routeGre = solution.getRoute();

    // time end greedy
    auto stopGreedy = high_resolution_clock::now();

    cout << "##### Initial Solution #####" << endl;
    cout << "Route: ";
    for (int i = 0; i < routeGre.size(); i++)
    {
        cout << routeGre[i] << " ";
    }

    // gather the execution time and the solution value of the greedy construction
    int executionTimeGreedy = duration_cast<milliseconds>(stopGreedy - startGreedy).count();
    int solutionValueGreedy = solution.getSolutionValue();

    // print output
    cout << "\nSolution Value: " << solutionValueGreedy << endl;
    cout << "\nExecution time: " << executionTimeGreedy << "ms\n"
         << endl;
    cout << "############################\n"
         << endl;

    // time start vnd
    auto startVND = high_resolution_clock::now();

    // procedure
    solver.run(instance, solution);
    vector<int> routeVND = solution.getRoute();

    // time end vnd
    auto stopVND = high_resolution_clock::now();

    // gather the execution time and the solution value of the vnd
    int executionTimeVND = duration_cast<milliseconds>(stopVND - startVND).count();
    int solutionValueVND = solution.getSolutionValue();

    // print output
    cout << "###### Best Solution #######" << endl;
    cout << "Route: ";
    for (int i = 0; i < routeVND.size(); i++)
    {
        cout << routeVND[i] << " ";
    }
    cout << "\nSolution Value: " << solutionValueVND << endl;
    cout << "\nExecution time: " << executionTimeVND << "ms\n"
         << endl;
    cout << "############################" << endl;

    // export the results
    // instance name
    string instanceName = argv[1];
    // substring to remove the path and the extension of the instance
    instanceName = instanceName.substr(instanceName.find_last_of("/") + 1, instanceName.find_last_of(".") - instanceName.find_last_of("/") - 1);
    // txt file name
    string instanceResult = "../output/" + instanceName + ".txt";
    // call the function to export the results
    exportResults(instanceResult, solution, routeGre, executionTimeGreedy, solutionValueGreedy, routeVND, executionTimeVND, solutionValueVND);

    return 0;
}