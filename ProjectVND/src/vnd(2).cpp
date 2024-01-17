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

    for (int i = 1; i < currentSolution.getRoute().size() - 1; i++){
        for (int j = 1; j < currentSolution.getRoute().size() - 1; j++){
            if (i != j){
                route = currentSolution.getRoute();
                std::swap(route[i], route[j]);

                for (int k = 0; k < route.size()-1; k++){
                    solValue += instance.getDistanceMatrix()[route[k]][route[k + 1]];
                }
                if(solValue < bestSwap.getSolutionValue()){
                    bestSwap.setRoute(route);
                    bestSwap.setSolutionValue(solValue);
                }
            }
            solValue = 0;
        }
    }
    return bestSwap;
}
	
Solution VND::opt2(Instance &instance, Solution currentSolution)
{

}
	
Solution VND::reinsertion(Instance &instance, Solution currentSolution)
{

}

void VND::run(Instance &instance, Solution &currentSolution)
{
    int selected_neighborhood = 1;
    Solution bestSolution;

    while (selected_neighborhood <= N_NEIGHBORHOOD){
        switch (selected_neighborhood){
            case 1:
                /**** Swap ****/
                //cout << "Swap" << endl;
                bestSolution = swap(instance, currentSolution);

                if(bestSolution.getSolutionValue() < currentSolution.getSolutionValue()){
                    currentSolution = bestSolution;
                    selected_neighborhood = 1;
                }
                else{
                    selected_neighborhood++;
                }
                break;
            case 2:
                /**** 2-opt ****/
                //cout << "2-opt" << endl;
                bestSolution = opt2(instance, currentSolution);

                if(bestSolution.getSolutionValue() < currentSolution.getSolutionValue()){
                    currentSolution = bestSolution;
                    selected_neighborhood = 2;
                }
                else{
                    selected_neighborhood++;
                }
                break;
            case 3:
                /**** Reinsertion ****/
                //cout << "Reinsertion" << endl;
                bestSolution = reinsertion(instance, currentSolution);

                if(bestSolution.getSolutionValue() < currentSolution.getSolutionValue()){
                    currentSolution = bestSolution;
                    selected_neighborhood = 3;
                }
                else{
                    selected_neighborhood++;
                }
                break;
            default:
                break;
        }
    }
}