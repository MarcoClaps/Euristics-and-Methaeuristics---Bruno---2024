#include "../include/vnd.hpp"

VND::VND()
{
}

VND::~VND()
{
}

int VND::calculate_delta_swap(int i, int j, const vector<vector<double>> &distance_matrix)
{

    // int n = path.size();
    // int a = path[i];
    // int b = path[(i + 1) % n];
    // int c = path[j];
    // int d = path[(j + 1) % n];

    // double current_distance = distance_matrix[a][b] + distance_matrix[c][d];
    // double new_distance = distance_matrix[a][c] + distance_matrix[b][d];

    double current_distance = distance_matrix[i - 1][i] + distance_matrix[i][i + 1] + distance_matrix[j - 1][j] + distance_matrix[j][j + 1];
    double new_distance = distance_matrix[i - 1][j] + distance_matrix[j][i + 1] + distance_matrix[j - 1][i] + distance_matrix[i][j + 1];

    return new_distance - current_distance;
}

int VND::calculate_delta_2Opt(int i, int j, int k, int l, const vector<vector<double>> &distance_matrix)
{

    double current_distance = distance_matrix[i][j] + distance_matrix[k][l];
    double new_distance = distance_matrix[i][k] + distance_matrix[j][l];

    return new_distance - current_distance;
}

int VND::calculate_delta_reins(const vector<int> &path, int i, int j, const vector<vector<double>> &distance_matrix)
{

    // int n = path.size();
    // int a = path[i];
    // int b = path[(i + 1) % n];
    // int c = path[j];
    // int d = path[(j + 1) % n];

    // double current_distance = distance_matrix[a][b] + distance_matrix[c][d];
    // double new_distance = distance_matrix[a][c] + distance_matrix[b][d];

    double current_distance = distance_matrix[i - 1][i] + distance_matrix[i][i + 1] + distance_matrix[j - 1][j] + distance_matrix[j][j + 1];
    double new_distance = distance_matrix[i - 1][j] + distance_matrix[j][i + 1] + distance_matrix[j - 1][i] + distance_matrix[i][j + 1];

    return new_distance - current_distance;
}

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
            int delta = calculate_delta_swap(i, j, instance.getDistanceMatrix());
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

            int k = i;
            int l = j;
            while (k < l)
            {

                int delta = calculate_delta_2Opt(i, i+1, j, j+1, instance.getDistanceMatrix());
                if (delta < 0)
                {
                    std::swap(route[k], route[l]);
                }
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