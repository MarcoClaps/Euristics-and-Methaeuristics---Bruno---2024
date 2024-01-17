#include <iostream>
#include <string>
#include <vector>
#include <chrono>

int main() {
    // Integer type
    int num = 10;
    
    // Double type
    double pi = 3.14159;

    // Chat type
    char char1 = 'a';
    char char2 = 43;
    
    // String type
    std::string greeting = "Hello, ";
    
    // Boolean type
    bool isTrue = true;

    std::cout << "Integer: " << num << std::endl;
    std::cout << "Double: " << pi << std::endl;
    std::cout << "Char 1: " << char1 << std::endl;
    std::cout << "Char 2: " << char2 << std::endl;
    std::cout << "String: " << greeting << "World!" << std::endl;
    std::cout << "Boolean: " << std::boolalpha << isTrue << std::endl;

    return 0;
}