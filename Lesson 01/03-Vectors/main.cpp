#include <iostream>
#include <vector>

int main() {
    // Creating a vector of integers
    std::vector<int> numbers;

    // Adding elements to the vector
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);

    // Accessing elements using index
    std::cout << "Elements in the vector:" << std::endl;
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;

    // Using iterators to access elements
    std::cout << "Elements using iterators:" << std::endl;
    for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Alternative code 
    std::cout << "Elements using iterators:" << std::endl;
    for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Using range-based for loop (C++11 and later)
    std::cout << "Elements using range-based for loop:" << std::endl;
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Accessing the first and last element
    std::cout << "First element: " << numbers.front() << std::endl;
    std::cout << "Last element: " << numbers.back() << std::endl;

    // Inserting an element at a specific position
    numbers.insert(numbers.begin() + 1, 15);

    std::cout << "Elements after inserting 15 at index 1:" << std::endl;
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Removing the last element
    numbers.pop_back();

    std::cout << "Elements after removing the last element:" << std::endl;
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Clearing all elements from the vector
    numbers.clear();

    std::cout << "Size of the vector after clearing: " << numbers.size() << std::endl;

    return 0;
}
