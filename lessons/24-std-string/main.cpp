/* C-style string variables behave oddly, are hard to work with

- e.g. you can’t use assignment to assign a C-style string variable a new value
- e.g. if you copy a larger C-style string into the space allocated for a shorter C-style string, undefined behavior will result.

- C++ has introduced std::string and std::string_view (C++17). 
- std::string and std::string_view aren’t fundamental types (they’re class types).
*/

/* String input with std::cin

std::cout << "Enter your full name: ";
std::string name{};
std::cin >> name; // this won't work as expected since std::cin breaks on whitespace

std::cout << "Enter your favorite color: ";
std::string color{};
std::cin >> color;

std::cout << "Your name is " << name << " and your favorite color is " << color << '\n';

Output:
Enter your full name: John Doe
Enter your favorite color: Your name is John and your favorite color is Doe

- operator>> only returns characters up to the first whitespace it encounters.

=> Use std::getline()
*/

#include <iostream>
#include <string> // allows use of std::string, std::getline

int main()
{
    std::cout << "Hello, world!"; // "Hello world!" is a C-style string literal.

    std::string name {}; // empty string
    std::string name2 { "Alex" }; // initialize name with string literal "Alex"
    name2 = "Johnnnn";               // change name to "John"
    // If std::string doesn’t have enough memory to store a string, 
    // it will request additional memory (at runtime) using dynamic memory allocation.

    std::cout << "Enter your full name: ";
    std::getline(std::cin >> std::ws, name); // read a full line of text into name
    // The std::ws input manipulator tells std::cin to ignore any leading whitespace
    // (spaces, tabs, newlines) at the start of the string.
    // This needs to be done for each std::getline() call, as std::ws is not preserved across calls.

    std::cout << name << " has " << name.length() << " characters\n";
    // Although std::string is required to be null-terminated (as of C++11), 
    // the returned length of a std::string does not include it.

    // If you want to assign the length to an int variable, you should static_cast 
    // it to avoid compiler warnings about signed/unsigned conversions:
    int length { static_cast<int>(name.length()) };

    // Double-quoted string literals (like “Hello, world!”) are C-style strings by default.
    using namespace std::string_literals; // easy access to the s suffix
    std::cout << "foo\n";   // no suffix is a C-style string literal
    std::cout << "goo\n"s;  // s suffix is a std::string literal

    return 0;
}

/* 
- Initializing a std::string is expensive (a copy of the string used to initialize it is made.)
- When a std::string is passed to a function by value, this results in an expensive copy.
  We’ll discuss what to do instead (use std::string_view).
- However, it is okay when a function returns a std::string by value to the caller.
  std::string supports "move semantics", which allows an object that will be destroyed 
  at the end of the function to instead be returned by value without making a copy.
*/

/* constexpr std::string isn’t supported at all in C++17 or earlier

- and only works in very limited cases in C++20/23. 
- If you need constexpr strings, use std::string_view instead
*/

/* References

- https://www.learncpp.com/cpp-tutorial/introduction-to-stdstring/
*/