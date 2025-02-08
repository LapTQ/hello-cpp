/* Array decay

Imagine you want to write a function that accepts a C-style array. There are 2 challenges:
- Expensive copy if the array is large.
    But C language doesn't have reference.
- We want a single function that can accept arrays of different sizes.
    ```
    void printElementZero(int arr[1000]);
    ```
    But C has no syntax to specify "any length" array or template.

The designer of C came up with a clever solution that solve both challenges: array decay.
- In most cases, when a C-style array is used in an expression, the array will be implicitly 
  converted into a pointer, initialized with the address of the first element (with index 0).
*/


/* Subscripting a C-style array actually applies operator[] to the decayed pointer
*/


/* Solve the 2 challenges
*/

#include <iostream>
#include <iterator>

void printElementZero(const int* arr) // pass by const address
{
    std::cout << arr[0];
}


/* C-style array function parameter syntax

- One problem with declaring the function parameter as `int* arr`
  is that it’s not obvious that arr is supposed to be a 
  "pointer to an array" rather than a pointer to a single integer.
=> when passing a C-style array, its preferable to use the 
   alternate declaration form `int arr[]` (treated the same as `int* arr`)

- The downside of using this syntax is that it makes it less obvious that arr has decayed.
*/

void printElementZero2(const int arr[]) // pass by const address
{
    std::cout << arr[0];
}


/* The problems with array decay

- sizeof() will return different values for arrays and decayed arrays.
- perhaps most importantly, array decay can make refactoring difficult.
- Loss of length information.
    Historically, programmers worked around using one of the 2 methods:
    + pass the length of the array as a separate parameter. Issues:
        - sign conversion issues
        - cannot do compile-time validation
        - only work with explicit call. If the array is passed as operand, we cannot pass in the length.
    + mark the end of the array using an element that not sematically valid. Issues:
        - need special handling for the terminating element.
        - mismatch between the array actual length and the number of semantically valid elements.

=> C-style arrays should be avoided in most cases.
*/

void printArraySize(int arr[])
{
    std::cout << sizeof(arr) << '\n'; // prints 4 (assuming 32-bit addresses)
}

#include <iomanip> // for std::boolalpha


int main()
{
    // array decay
    int arr1[] { 1, 2, 3, 4, 5 };
    auto ptr{ arr1 }; // evaluation cause arr1 to decay, to type deduction should deduce type int*
    std::cout << std::boolalpha << (typeid(ptr) == typeid(int*)) << '\n'; // true, prove that array is decayed to pointer
    std::cout << std::boolalpha << (&arr1[0] == ptr) << '\n'; // true, prove that ptr is pointing to the first element of arr1


    // Subscripting a C-style array actually applies operator[] to the decayed pointer
    const int arr2[] { 1, 2, 3, 4, 5 };
    std::cout << arr2[1] << '\n'; // 2
    const int* ptr2{ arr2 };
    std::cout << ptr2[1] << '\n'; // 2, same as arr2[1]


    // Solve the 2 challenges
    printElementZero(arr1); // 1


    // The problems with array decay
    printArraySize(arr1); // 4
    std::cout << sizeof(arr1) << '\n'; // 20 (5 * 4)
}


/* In C++, there are a few common cases where an C-style array doesn’t decay:

- When used as an argument to sizeof() or typeid().
- When taking the address of the array using operator&.
- When passed as a member of a class type.
- When passed by reference.
*/


/* References

- https://www.learncpp.com/cpp-tutorial/c-style-array-decay/
*/