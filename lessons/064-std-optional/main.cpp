/*
- How to handle if user input y = 0?
*/

int doIntDivision(int x, int y)
{
    return x / y;
}

/* (C++17) Returning a std::optional

- std::optional is a class template type that implements an optional value.
  That is, a std::optional<T> can either have a value of type T, or not,
*/

#include <iostream>
#include <optional> // for std::optional (C++17)

std::optional<int> doIntDivision2(int x, int y)
{
    if (y == 0)
        return {}; // or return std::nullopt
    return x / y;
}

int main()
{
    std::optional<int> result1 { doIntDivision2(20, 5) };
    if (result1) // if the function returned a value
        std::cout << "Result 1: " << *result1 << '\n';
    else
        std::cout << "Result 1: failed\n";

    
    // use std::optional is easy
    std::optional<int> o1 { 5 };            // initialize with a value
    std::optional<int> o2 {};               // initialize with no value
    std::optional<int> o3 { std::nullopt }; // initialize with no value

    // check if the optional has a value
    if (o1.has_value()); // call has_value() to check if o1 has a value
    if (o2);        // use implicit conversion to bool

    // get the value
    std::cout << *o1;             // dereference (undefined behavior if o1 does not have a value)
    std::cout << o2.value();      // throws std::bad_optional_access exception if o2 does not have a value
    std::cout << o3.value_or(42); //  value `42` if o3 doesn't have a value

    return 0;
}

/* semantically, a pointer and a std::optional are quite different.

- A pointer has reference semantics. Local objects are destroyed.
- A std::optional has value semantics. Local objects are copied.
  Unfortunately, as of C++23 std::optional does not support references.

=> we recommend using std::optional<T> as an optional parameter 
   only when T would normally be passed by value. Otherwise, use const T*.
*/


/* References

- https://www.learncpp.com/cpp-tutorial/stdoptional/
*/