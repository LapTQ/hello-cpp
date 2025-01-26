#include <iostream>

int main() {
    char ch2 { 'a' };
    std::cout << ch2 << '\n'; // a

    char ch1 { 97 }; // 97 is the ASCII code for 'a'
    std::cout << ch1 << '\n'; // a

    std::cout << "Input a keyboard character: "; // assume the user enters "a b"
    char ch{};
    std::cin >> ch; // extracts a, leaves " b\n" in stream
    std::cout << "You entered: " << ch << '\n';
    std::cin >> ch; // skips leading whitespace (the space), extracts b, leaves "\n" in stream
    std::cout << "You entered: " << ch << '\n';
    
    
    std::cout << "Input a keyboard character: "; // assume the user enters "a b"
    std::cin >> ch; // extracts a, leaves " b\n" in stream
    std::cout << "You entered: " << ch << '\n';
    std::cin.get(ch); // extracts space, leaves "b\n" in stream
    std::cout << "You entered: " << ch << '\n';

    return 0;
}


/*
- The char data type is an integral type, meaning the underlying value is stored as an integer.
- Character literals are always placed between single quotes (e.g. ‘g’, ‘1’, ‘ ‘).
*/

/* Inputting chars

- Note that std::cin will let you enter multiple characters. 
- However, variable ch can only hold 1 character. Consequently, only the first input character is 
  extracted into variable ch. The rest of the user input is left in the input buffer that std::cin uses.
*/

/* Char size, range, and default sign

- Char is defined by C++ to always be 1 byte in size.
- you don’t need to specify a sign (since both signed and unsigned chars can hold values between 0 and 127).
*/

/* Extracting whitespace characters

- extracting input ignores leading whitespace, this can lead to unexpected results .
- One simple way is to use the std::cin.get(), as this function does not ignore leading whitespace.
*/

/* Avoid multicharacter literals

- Many C++ compilers support multicharacter literals (e.g. '56'). It depends on the compiler. 
  Because they are not part of the C++ standard, and their value is not strictly defined, multicharacter literals should be avoided.
*/


/* References

- https://www.learncpp.com/cpp-tutorial/chars/
*/