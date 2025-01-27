/* `delete` specifier

- If the compiler matches a function call to a deleted function, compilation will be halted with a compile error.
*/


#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}

void printInt(bool) = delete; // calls to this function will halt compilation

int main()
{
    printInt(5);    // okay: prints 5
    printInt('a');  // prints 97, does not make sense
    printInt(true); // would print 1, but compile error: function deleted

    printInt(5.0);  // compile error: ambiguous match
    // because the deleted functions are still considered as candidates in function overload resolution. 

    return 0;
}

/* Deleting all non-matching overloads:


void printInt(int x) // This function will take precedence for arguments of type int

template <typename T>
void printInt(T x) = delete; // This function will take precedence for all other types


*/

/* References

- https://www.learncpp.com/cpp-tutorial/deleting-functions/
*/