/*
- copying is typically expensive for class types.
- When passing arguments into a function by value, a copy of the argument is made.
- We encounter a similar situation when returning by value: a copy of the return value is passed back to the caller.
*/

/* Return by reference

- Be aware of dangling references. The object being returned by reference must exist after the function returns.

- Attention: assign a reference to a non-reference variable will copy the value.
*/

/* Solution: return reference parameters by reference
*/

int& max(int& x, int& y)
{
    return (x > y) ? x : y;
}

#include <iostream>

int main()
{
    // assign a reference to a non-reference variable will copy the value
    int x { 5 };
    int& ref { x };
    int y { ref }; // y is now a copy of x
    std::cout << &x << '\n';    // 0x7ffc70904a60
    std::cout << &ref << '\n';  // 0x7ffc70904a60 (same as x)
    std::cout << &y << '\n';    // 0x7ffc70904a64 (different from x)


    // return reference parameters by reference
    int a{ 5 };
    int b{ 6 };
    max(a, b) = 7; // sets the greater of a or b to 7
    std::cout << a << b << '\n';  // 57

    return 0;
}


/* Return by address

- Return by address works almost identically to return by reference,

- The major advantage of return by address over return by reference 
  is that we can have the function return nullptr if there is no valid object to return.
  If you need the ability to return “no object” or a value (rather than an object),
  std::optional describes a good alternative (discuss later).
*/


/* References

- https://www.learncpp.com/cpp-tutorial/return-by-reference-and-return-by-address/
- https://www.learncpp.com/cpp-tutorial/in-and-out-parameters/
*/