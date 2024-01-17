#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;


// Function to remove all even numbers from a vector
void removeEvenNumbers(vector<int> &vec) {
    int i = 0;
    while (i < vec.size()) {
        if (vec[i] % 2 == 0) {
            vec.erase(vec.begin() + i); // Erase even number at index i
        } else {
            ++i; // Move to the next element
        }
    }
}

int main(){
    auto start = high_resolution_clock::now(); // Get a reference for the start time
    
    // Generating a large vector with 500k elements
    vector<int> values;
    for(int i = 0; i < 500000; ++i){
        values.push_back(i);
    }

    // Remove even numbers
    removeEvenNumbers(values);


    // Measure the runtime
    auto end = high_resolution_clock::now(); // Get a reference for the end time
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Total time: " << duration.count() << "ms" << endl;

    return 0;
}
