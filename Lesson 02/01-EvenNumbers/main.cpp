#include <iostream>
#include <vector>
#include <list>
#include <chrono>

using namespace std;
using namespace std::chrono;


/***********************************************************************************
*  removeEvenNumbers
*
*  @brief Function to remove all even numbers from a vector
*
*  @param vec (vector<int> &): the input array
*
***********************************************************************************/
void removeEvenNumbers1(vector<int> &vec) {
    int i = 0;
    while (i < vec.size()) {
        if (vec[i] % 2 == 0) {
            vec.erase(vec.begin() + i); // Erase even number at index i
        } else {
            ++i; // Move to the next element
        }
    }
}

void removeEvenNumbers2(vector<int> &vec) {
    int i = vec.size() - 1;
    while (i >= 0) {
        if (vec[i] % 2 == 0) {
            vec.erase(vec.begin() + i); // Erase even number at index i
        }
        --i; // Move to the previous element
    }
}

void removeEvenNumbers3(vector<int> &vec) {
    vector<int> oddNumbers;
    for (int num : vec) {
        if (num % 2 != 0) {
            oddNumbers.push_back(num);
        }
    }
    vec = oddNumbers; // Assign the vector with only odd numbers back to the original vector
}

void removeEvenNumbers4(vector<int> &vec) {
    vector<int> oddNumbers;
    oddNumbers.reserve(vec.size() / 2);
    for (int num : vec) {
        if (num % 2 != 0) {
            oddNumbers.push_back(num);
        }
    }
    vec = oddNumbers; // Assign the vector with only odd numbers back to the original vector
}

void removeEvenNumbers5(vector<int> &vec) {

    int remove_if(vector<int>::iterator first, vector<int>::iterator last, bool (*pred)(int)){
        
    }

    vec.erase(remove_if(vec.begin(), vec.end(), [](int num) { return num % 2 == 0; }), vec.end());
}

void removeEvenNumbers6(vector<int>& vec) {
    int writeIdx = 0;
    for (int readIdx = 0; readIdx < vec.size(); ++readIdx) {
        if (vec[readIdx] % 2 != 0) {
            if (readIdx != writeIdx) {
                swap(vec[writeIdx], vec[readIdx]);
            }
            ++writeIdx;
        }
    }
    vec.resize(writeIdx); // Resize to remove the even numbers at the end
}

void removeEvenNumbers7(list<int> &lst) {
    auto it = lst.begin();
    while (it != lst.end()) {
        if (*it % 2 == 0) {
            it = lst.erase(it); // Erase even number and get the iterator to the next element
        } else {
            ++it; // Move to the next element
        }
    }
}

/***********************************************************************************
*  createVector
*
*  @brief Create the test vector from scratch
*
*  @param size (int): the size of the array
*
*  @return [vector<int>] the test vector
***********************************************************************************/
vector<int> createVector(int size){
    vector<int> values(size);
    for (int i = 0; i < size; ++i){
        values[i] = i;
    }

    return values;
}

/***********************************************************************************
*  createList
*
*  @brief Create the test list from scratch
*
*  @return [list<int>] the test list
***********************************************************************************/
list<int> createList(int size){
    list<int> values;
    for (int i = 0; i < size; ++i){
        values.push_back(i);
    }

    return values;
}

/***********************************************************************************
*  MAIN
***********************************************************************************/
int main(int argc, char* argv[]){
    int  num_test_samples = 1
        ,type = 1
        ,array_size = 500000;
    unsigned int sum_time = 0;
    
    // Parse command line arguments
    for (int i = 1 ; i < argc; ++i) {
        // Number of samples
        if(string(argv[i]) == "--samples" && i + 1 < argc) {
            num_test_samples = atoi(argv[i + 1]);
        } 
        // Specify which version of the function to use
        else if (string(argv[i]) == "--type" && i + 1 < argc) {
            type = atoi(argv[i + 1]);
        }
        // Array size
        else if (string(argv[i]) == "--array_size" && i + 1 < argc) {
            array_size = atoi(argv[i + 1]);
        }
    }


    // Run the code multiple times to get a better estimation of the average runtime
    for(int i = 0 ; i < num_test_samples ; i++){
        auto start = high_resolution_clock::now(); // Get a reference for the start time    

        // Run the test based on the chosen function type
        switch(type){
            case 1:{
                vector<int> values = createVector(array_size);
                removeEvenNumbers1(values);
                break;
            }
            case 2:{
                vector<int> values = createVector(array_size);
                removeEvenNumbers2(values);
                break;
            }
            case 3:{
                vector<int> values = createVector(array_size);
                removeEvenNumbers3(values);
                break;
            }
            case 4:{
                vector<int> values = createVector(array_size);
                removeEvenNumbers4(values);
                break;
            }
            case 5:{
                vector<int> values = createVector(array_size);
                removeEvenNumbers5(values);
                break;
            }
            case 6:{
                vector<int> values = createVector(array_size);
                removeEvenNumbers6(values);
                break;
            }
            case 7:{
                list<int> values = createList(array_size);
                removeEvenNumbers7(values);
                break;
            }
        
            default:
                cerr << "Invalid type!" << endl;
                break;
        }
        
        // Measure the runtime
        auto end = high_resolution_clock::now(); // Get a reference for the end time
        auto duration = duration_cast<milliseconds>(end - start);
        sum_time += duration.count();
    } 

    // Evaluate the average time
    double average = (double) sum_time / num_test_samples;
    cout << "Average time of version " << type << ": " << average << "ms" << endl;

    return 0;
}
