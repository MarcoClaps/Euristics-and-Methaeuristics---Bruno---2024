#include "../include/vnd.hpp"

VND::VND()
{
}

VND::~VND()
{
}

int VND::calculate_delta_swap_2opt_Marco(const vector<int> &path, int i, int j, const vector<vector<double>> &distance_matrix)
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

int VND::calculate_delta_swap_2opt_Salvo(const vector<int> &path, int i, int j, const vector<vector<double>> &distance_matrix)
{
    int n = path.size();

    // Calcola la differenza nella distanza totale dopo l'applicazione di 2-opt
    int a = path[i];
    int b = path[(i + 1) % n]; // Utilizzando l'operatore modulo % n, garantiamo che l'indice risultante sia sempre all'interno dei limiti validi del vettore del percorso.
    // rappresenta il punto successivo a path[i] nel percorso. Se i è l'ultimo elemento del vettore (n-1), l'operatore % n riporterà a 0, consentendo il collegamento circolare.
    int c = path[j];
    int d = path[(j + 1) % n]; // rappresenta il nodo successivo a path[j] nel percorso. Stessa logica di cui sopra, se j è l'ultimo elemento del vettore (n-1), l'operatore % n riporterà a 0.

    double current_distance = distance_matrix[a][b] + distance_matrix[c][d];
    double new_distance = distance_matrix[a][c] + distance_matrix[b][d];

    return new_distance - current_distance;
}

int VND::calculate_delta_reinsertion(const vector<int> &path, int removed_index, int insert_index, const vector<vector<double>> &distance_matrix)
{
    int n = path.size();
    // Calcola la differenza nella distanza totale dopo l'inserimento
    int a = path[(removed_index - 1 + n) % n];
    int b = path[removed_index];
    int c = path[(removed_index + 1) % n];
    int d = path[insert_index];

    double current_distance = distance_matrix[a][b] + distance_matrix[b][c] + distance_matrix[d][path[insert_index + 1]];
    double new_distance = distance_matrix[a][c] + distance_matrix[d][b] + distance_matrix[b][path[insert_index + 1]];

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
            int delta = calculate_delta_swap_2opt_Marco(currentSolution.getRoute(), i, j, instance.getDistanceMatrix());
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
            int delta = calculate_delta_swap_2opt_Salvo(currentSolution.getRoute(), i, j, instance.getDistanceMatrix());
            if (delta < 0)
            {
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
            int delta = calculate_delta_reinsertion(route, i, j, instance.getDistanceMatrix());
            if (delta < 0)
            {
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