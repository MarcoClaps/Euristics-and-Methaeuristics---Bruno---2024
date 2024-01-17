#include "../include/instance.hpp"
#include "../include/vnd.hpp"
#include "../include/solution.hpp"
#include <iostream>
#include <float.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

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

    Instance instance(pathInstance);
    instance.readMatrix();
    // instance.printMatrix();

    // time start greedy
    auto startGreedy = high_resolution_clock::now();
    Solution solution = greedyConstruction(instance);
    vector<int> route = solution.getRoute();
    // time end greedy
    auto stopGreedy = high_resolution_clock::now();

    cout << "##### Initial Solution #####" << endl;
    cout << "Route: ";
    for (int i = 0; i < route.size(); i++)
    {
        cout << route[i] << " ";
    }
    cout << "\nSolution Value: " << solution.getSolutionValue() << endl;
    cout << "\nExecution time: " << duration_cast<milliseconds>(stopGreedy - startGreedy).count() << "ms\n"
         << endl;
    cout << "############################\n"
         << endl;

    // time start vnd
    auto startVND = high_resolution_clock::now();
    solver.run(instance, solution);
    route = solution.getRoute();
    // time end vnd
    auto stopVND = high_resolution_clock::now();

    cout << "###### Best Solution #######" << endl;
    cout << "Route: ";
    for (int i = 0; i < route.size(); i++)
    {
        cout << route[i] << " ";
    }
    cout << "\nSolution Value: " << solution.getSolutionValue() << endl;
    cout << "\nExecution time: " << duration_cast<milliseconds>(stopVND - startVND).count() << "ms\n"
         << endl;
    cout << "############################" << endl;

    return 0;
}