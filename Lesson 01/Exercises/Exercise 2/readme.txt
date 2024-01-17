Suggested strategy;
    1) Create a function that reads the txt file and returns an array of strings.
    Each line of the file is a string of this array. This could be useful because
    you can iterate on a string in the same way as you do for a vector. Each element
    of the string is of type char
    2) Create a function that parses each line, looking for the first and last digit 
    and returns the resulting calibration value

Tips:
    - Given that you do not know how many lines the file has, you might want to take a
        look at the function eof from ifstream (https://cplusplus.com/reference/ios/ios/eof/)
        which helps in knowing when you reach the end of the file
    - There is a function from the standard library called isdigit that can be useful
        (https://cplusplus.com/reference/cctype/isdigit/)
    - If you have a variable of type string you can add characters to the end of it like a vector by 
    using push_back or simply +=. For example, consider a variable s of type string:
        s += 'a'; // This would append the character 'a' to the end of the string
        s.push_back('a'); // This does the same
    - If you want to convert a string variable named s into an integer you can use the following code:
    int i = atoi(s.c_str());