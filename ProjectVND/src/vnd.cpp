#include "../include/vnd.hpp"

VND::VND()
{
}

VND::~VND()
{
}

/**
 * @brief Computes the difference in total distance switching two nodes (Swap)
 *
 * @param path
 * @param i
 * @param j
 * @param distance_matrix
 * @return int
 */
int VND::calculate_delta_swap(int i, int j, const vector<vector<double>> &distance_matrix)
{
    double current_distance = distance_matrix[i - 1][i] + distance_matrix[j][j + 1];
    double new_distance = distance_matrix[i - 1][j] + distance_matrix[i][j + 1];
    if (i + 1 != j)
    {
        current_distance += distance_matrix[i][i + 1] + distance_matrix[j - 1][j];
        new_distance += distance_matrix[j][i + 1] + distance_matrix[j - 1][i];
    }

    return new_distance - current_distance;
}

/**
 * @brief Computes the difference in total distance in a possible 2-opt move
 *
 * @param path
 * @param i
 * @param j
 * @param distance_matrix
 * @return int
 */
int VND::calculate_delta_2opt(const vector<int> &path, int i, int j, const vector<vector<double>> &distance_matrix)
{
    int n = path.size();

    // a is the node at index i
    int a = path[i];
    // b is the node after a. With the modulo operator % n, we ensure that the resulting index is always within the valid limits of the path vector.
    // if i = n - 1, then (i + 1) % n = 0, which is the first node of the path.
    int b = path[(i + 1) % n];
    // c is the node at index j
    int c = path[j];
    // d is the node after c. Same logic as above.
    int d = path[(j + 1) % n];

    double current_distance = distance_matrix[a][b] + distance_matrix[c][d];
    double new_distance = distance_matrix[a][c] + distance_matrix[b][d];

    return new_distance - current_distance;
}

/**
 * @brief Computes the difference in total distance in a possible reinsertion move
 *
 * @param path
 * @param removed_index
 * @param insert_index
 * @param distance_matrix
 * @return int
 */
int VND::calculate_delta_reinsertion(const vector<int> &path, int removed_index, int insert_index, const vector<vector<double>> &distance_matrix)
{
    int n = path.size();

    // a is the index before the removed node
    int a = path[(removed_index - 1 + n) % n];
    // b is the index of the removed node
    int b = path[removed_index];
    // c is the index after the removed node
    int c = path[(removed_index + 1) % n];
    // d is the index at which the removed node will be inserted
    int d = path[insert_index];

    double current_distance = distance_matrix[a][b] + distance_matrix[b][c] + distance_matrix[d][path[insert_index + 1]];
    double new_distance = distance_matrix[a][c] + distance_matrix[d][b] + distance_matrix[b][path[insert_index + 1]];

    return new_distance - current_distance;
}

/**
 * @brief Local search - Swap. First compute the delta of the swap, if it is negative, then swap the nodes.
 *
 * @param instance
 * @param currentSolution
 * @return Solution
 */
Solution VND::swap(Instance &instance, Solution currentSolution)
{
    vector<int> route;
    double solValue = 0;
    Solution bestSwap;
    bestSwap.setSolutionValue(currentSolution.getSolutionValue());

    for (int i = 1; i < currentSolution.getRoute().size() - 1; i++)
    {
        for (int j = i + 1; j < currentSolution.getRoute().size() - 1; j++)
        {
            int delta = calculate_delta_swap( i, j, instance.getDistanceMatrix());
            if (delta >= 0)
            {
                continue;
            }

            route = currentSolution.getRoute();
            std::swap(route[i], route[j]);

            for (int k = 0; k < route.size() - 1; k++)
            {
                solValue += instance.getDistanceMatrix()[route[k]][route[k + 1]];
            }
            if (solValue < bestSwap.getSolutionValue())
            {
                bestSwap.setRoute(route);
                bestSwap.setSolutionValue(solValue);

                // Print best solution
                // cout << "Improvement solution - Swap: ";
                // for (int k = 0; k < route.size() - 1; k++)
                // {
                //     cout << route[k] << " ";
                // }
                // cout << endl;
            }
        }
        solValue = 0;
    }
    return bestSwap;
}

/**
 * @brief Local search - 2-opt. First compute the delta of the 2-opt, if it is negative, then swap the nodes.
 *
 * @param instance
 * @param currentSolution
 * @return Solution
 *
 */
Solution VND::opt2(Instance &instance, Solution currentSolution)
{
    vector<int> route;
    double solValue = 0;
    Solution best2Opt;
    best2Opt.setSolutionValue(currentSolution.getSolutionValue());

    for (int i = 1; i < currentSolution.getRoute().size() - 1; i++)
    {
        for (int j = i + 2; j < currentSolution.getRoute().size() - 1; j++)
        {
            route = currentSolution.getRoute();

            // cout << " Route " << i << " " << j << " ";
            // for (int k = 0; k < route.size() - 1; k++)
            // {
            //     cout << route[k] << " ";
            // }
            // cout << endl;
            int delta = calculate_delta_2opt(currentSolution.getRoute(), i, j, instance.getDistanceMatrix());
            if (delta >= 0)
                continue;
            int k = i;
            int l = j;
            while (k < l)
            {
                std::swap(route[k], route[l]);
                k++;
                l--;
            }

            for (int k = 0; k < route.size() - 1; k++)
            {
                solValue += instance.getDistanceMatrix()[route[k]][route[k + 1]];
            }
            if (solValue < best2Opt.getSolutionValue())
            {
                best2Opt.setRoute(route);
                best2Opt.setSolutionValue(solValue);

                // Print best solution
                // cout << "Improvement solution - Opt-2: ";
                // for (int k = 0; k < route.size() - 1; k++)
                // {
                //     cout << route[k] << " ";
                // }
                // cout << endl;
            }
            solValue = 0;
        }
    }
    return best2Opt;
}

/**
 * @brief Local search - Reinsertion. First compute the delta of the reinsertion, if it is negative, then swap the nodes.
 *
 * @param instance
 * @param currentSolution
 * @return Solution
 *
 */
Solution VND::reinsertion(Instance &instance, Solution currentSolution)
{
    vector<int> route;
    double solValue = 0;
    Solution bestReinsert;
    bestReinsert.setSolutionValue(currentSolution.getSolutionValue());

    for (int i = 1; i < currentSolution.getRoute().size() - 1; i++)
    {
        for (int j = i + 1; j < currentSolution.getRoute().size() - 1; j++)
        {
            route = currentSolution.getRoute();

            // cout << " Route " << i << " " << j << " ";
            // for (int k = 0; k < route.size() - 1; k++)
            // {
            //     cout << route[k] << " ";
            // }
            // cout << endl;
            int delta = calculate_delta_reinsertion(route, i, j, instance.getDistanceMatrix());
            if (delta >= 0)
                continue;
                
            for (int k = i; k <= j; k++)
            {
                std::swap(route[k], route[k + 1]);
            }

            for (int k = 0; k < route.size() - 1; k++)
            {
                solValue += instance.getDistanceMatrix()[route[k]][route[k + 1]];
            }
            if (solValue < bestReinsert.getSolutionValue())
            {
                bestReinsert.setRoute(route);
                bestReinsert.setSolutionValue(solValue);

                // Print best solution
                // cout << "Improvement solution - ReInsert: ";
                // for (int k = 0; k < route.size() - 1; k++)
                // {
                //     cout << route[k] << " ";
                // }
                // cout << endl;
            }
            solValue = 0;
        }
    }
    return bestReinsert;
}

/**
 * @brief Run the VND algorithm. At first, the algorithm runs the Swap neighborhood, then the 2-opt neighborhood and finally the Reinsertion neighborhood. Every time it cannot improve the solution, it goes to the next neighborhood. If the solution is improved, the algorithm restarts the process from the first neighborhood.
 *
 * @param instance
 * @param currentSolution
 */

void VND::run(Instance &instance, Solution &currentSolution)
{
    int selected_neighborhood = 1;
    Solution bestSolution;

    while (selected_neighborhood <= N_NEIGHBORHOOD)
    {
        // cout << "Neighborhood: " << selected_neighborhood << endl;
        // selected_neighborhood = 3;
        switch (selected_neighborhood)
        {
        case 1:
            /**** Swap ****/
            // cout << "Swap" << endl;
            bestSolution = swap(instance, currentSolution);

            if (bestSolution.getSolutionValue() < currentSolution.getSolutionValue())
            {
                currentSolution = bestSolution;
                selected_neighborhood = 1;
            }
            else
            {
                selected_neighborhood++;
            }
            break;
        case 2:
            /**** 2-opt ****/
            // cout << "2-opt" << endl;
            bestSolution = opt2(instance, currentSolution);

            if (bestSolution.getSolutionValue() < currentSolution.getSolutionValue())
            {
                currentSolution = bestSolution;
                selected_neighborhood = 1;
            }
            else
            {
                selected_neighborhood++;
            }
            break;
        case 3:
            /**** Reinsertion ****/
            // cout << "Reinsertion" << endl;
            bestSolution = reinsertion(instance, currentSolution);

            if (bestSolution.getSolutionValue() < currentSolution.getSolutionValue())
            {
                currentSolution = bestSolution;
                selected_neighborhood = 1;
            }
            else
            {
                selected_neighborhood++;
            }
            break;
        default:
            selected_neighborhood++;
            break;
        }
    }
}