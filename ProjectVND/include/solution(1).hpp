#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>

using namespace std;

class Solution
{
private:
    /* data */
    vector<int> route;
    double solutionValue;
public:
    Solution();
    ~Solution();
    const vector<int>& getRoute();
    void setRoute(vector<int> &route);
    double getSolutionValue();
    void setSolutionValue(double value);
};

#endif