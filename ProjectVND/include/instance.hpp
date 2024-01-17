#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class Instance
{
private:
    /* data */
    string fileName;
    vector<vector<double>> distanceMatrix;

public:
    Instance(string fileName);
    ~Instance();
    void readMatrix();
    void printMatrix();
    const vector<vector<double>> &getDistanceMatrix();
};

#endif