#ifndef VND_H
#define VND_H

#include <vector>
#include "../include/instance.hpp"
#include "../include/solution.hpp"

#define N_NEIGHBORHOOD 3

using namespace std;

class VND
{
private:
    int calculate_delta_swap(const vector<int> &path, int i, int j, const vector<vector<double>> &distance_matrix);
    int calculate_delta_2opt(const vector<int> &path, int i, int j, const vector<vector<double>> &distance_matrix);
    int calculate_delta_reinsertion(const vector<int> &path, int i, int j, const vector<vector<double>> &distance_matrix);
    Solution swap(Instance &instance, Solution currentSolution);
    Solution opt2(Instance &instance, Solution currentSolution);
    Solution reinsertion(Instance &instance, Solution currentSolution);

public:
    VND();
    ~VND();
    void run(Instance &instance, Solution &currentSolution);
};

#endif