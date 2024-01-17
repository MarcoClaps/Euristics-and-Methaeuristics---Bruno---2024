#include <iostream>
#include <vector>
using namespace std;

// Function to calculate the factorial of a number recursively
int factorial(int n) {
    if (n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}

// Function to calculate the sum of elements in a vector
double vectorSum(const vector<double> &vec) {
    double sum = 0.0;
    for (double value : vec) {
        sum += value;
    }
    return sum;
}

// Function to swap two numbers using pass-by-reference with vectors
void swapVectorElements(vector<int> &vec, int index1, int index2) {
    if (index1 < vec.size() && index2 < vec.size()) {
        int temp = vec[index1];
        vec[index1] = vec[index2];
        vec[index2] = temp;
    } else {
        cout << "Indices out of range!" << endl;
    }
}

int main() {
    // Calling the factorial function
    int num = 5;
    cout << "Factorial of " << num << " is: " << factorial(num) << endl;

    // Calling the vectorSum function
    vector<double> values = { 1.2, 2.3, 3.4, 4.5, 5.6 };
    cout << "Sum of vector elements: " << vectorSum(values) << endl;

    // Swapping vector elements using the swapVectorElements function
    vector<int> nums = { 10, 20, 30, 40 };
    cout << "Before swapping - nums: ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;

    swapVectorElements(nums, 1, 2);

    cout << "After swapping - nums: ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
