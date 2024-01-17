#include "../include/solution.hpp"

Solution::Solution()
{
}

Solution::~Solution()
{
}

const vector<int> &Solution::getRoute()
{   
    return this->route;
}

void Solution::setRoute(vector<int> &route)
{
    this->route = route;
}

double Solution::getSolutionValue()
{
    return this->solutionValue;
}

void Solution::setSolutionValue(double value)
{
    this->solutionValue = value;
}