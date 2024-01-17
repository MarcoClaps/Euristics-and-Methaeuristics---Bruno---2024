#include "../include/vnd.hpp"

VND::VND()
{
}

VND::~VND()
{
}

Solution VND::swap(Instance &instance, Solution currentSolution)
{
    vector<int> route;
    double solValue = 0;
    Solution bestSwap;
    bestSwap.setSolutionValue(currentSolution.getSolutionValue());

    for (int i = 1; i < currentSolution.getRoute().size() - 1; i++)
    {
        for (int j = 1; j < currentSolution.getRoute().size() - 1; j++)
        {
            if (i != j)
            {
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
        for (int j = i + 1; j < currentSolution.getRoute().size() - 1; j++)
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
        case 3:
            /**** 2-opt ****/
            // cout << "2-opt" << endl;
            bestSolution = opt2(instance, currentSolution);

            if (bestSolution.getSolutionValue() < currentSolution.getSolutionValue())
            {
                currentSolution = bestSolution;
                selected_neighborhood = 2;
            }
            else
            {
                selected_neighborhood++;
            }
            break;
        case 2:
            /**** Reinsertion ****/
            // cout << "Reinsertion" << endl;
            bestSolution = reinsertion(instance, currentSolution);

            if (bestSolution.getSolutionValue() < currentSolution.getSolutionValue())
            {
                currentSolution = bestSolution;
                selected_neighborhood = 3;
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