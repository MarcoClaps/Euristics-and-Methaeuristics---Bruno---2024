Suggested strategy;
    1) Depending on how you did Exercise 2 you can reuse the function that reads the file
    2) Create a function that parses each line, looking for all the valid numbers on it
    and returns their sum
        - Once a complete number is found, you should verify whether it is valid.
        To do that it is recommended that you create another function that performs
        the validation

Tips:
    - Given that you do not know how many lines the file has, you might want to take a
        look at the function eof from ifstream (https://cplusplus.com/reference/ios/ios/eof/)
        which helps in knowing when you reach the end of the file
    - There is a function from the standard library called isdigit that can be useful
        (https://cplusplus.com/reference/cctype/isdigit/)
    - If you want to convert a string variable named s into an integer you can use the following code:
    int i = atoi(s.c_str());