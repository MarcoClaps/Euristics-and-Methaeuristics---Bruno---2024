#include "../include/solution.hpp"

Solution::Solution()
{
}

Solution::~Solution()
{
}

/*
 * @brief: get the route of the solution
 *
 * @return route: route of the solution
 */
const vector<int> &Solution::getRoute()
{
    return this->route;
}

/*
 * @brief: set the route of the solution
 *
 * @param route: route of the solution
 */
void Solution::setRoute(vector<int> &route)
{
    this->route = route;
}

/*
 * @brief: get the value of the solution
 *
 * @return value: value of the solution
 */
double Solution::getSolutionValue()
{
    return this->solutionValue;
}

/*
 * @brief: set the value of the solution
 *
 * @param value: value of the solution
 */
void Solution::setSolutionValue(double value)
{
    this->solutionValue = value;
}