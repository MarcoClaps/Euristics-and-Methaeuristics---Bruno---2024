#include "../include/instance.hpp"

Instance::Instance(string fileName)
{
    this->fileName = fileName;

}

Instance::~Instance()
{

}

void Instance::readMatrix()
{
    ifstream file(this->fileName);
    int dimension;

    if(file.is_open()){    
        file >> dimension;
        this->distanceMatrix.resize(dimension, vector<double>(dimension));

        for(int i = 0; i < dimension; i++){
            for(int j = 0; j < dimension; j++){
                file >> this->distanceMatrix[i][j];
            }
        }
    }
    else{
        cout << "Error reading the distance matrix" << endl;
        exit(-1);
    }
}

void Instance::printMatrix()
{
    for(int i = 0; i < this->distanceMatrix.size(); i++){
        for(int j = 0; j < this->distanceMatrix[i].size(); j++){
            cout << this->distanceMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

const vector<vector<double> >& Instance::getDistanceMatrix()
{
    return this->distanceMatrix;
}