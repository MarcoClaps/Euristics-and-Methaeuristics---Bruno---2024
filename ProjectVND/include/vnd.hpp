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
    Solution swap(Instance &instance, Solution currentSolution);
    Solution opt2(Instance &instance, Solution currentSolution);
    Solution reinsertion(Instance &instance, Solution currentSolution);

public:
    VND();
    ~VND();
    void run(Instance &instance, Solution &currentSolution);
};

#endif