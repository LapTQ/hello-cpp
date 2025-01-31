/* Null pointers

- Besides a memory address, there is one additional value that a pointer can hold: a null value.
- When a pointer is holding a null value, it means the pointer is not pointing at anything.

- create a null pointer:
    ```
    int* ptr {};
    int* ptr { nullptr };  // explicitly initialize a null pointer
    ptr = nullptr;         // assign a null pointer
    ```
*/

/* std::nullptr_t

-nullptr has type std::nullptr_t (defined in header <cstddef>).
*/

#include <iostream>

int main()
{
    int* ptr {};  // create a null pointer
    int* ptr2 { nullptr }; // explicitly initialize a null pointer
    ptr = nullptr; // assign a null pointer


    // Checking for null pointers
    if (ptr == nullptr) // explicit test for equivalence
        std::cout << "ptr is null\n";
    else
        std::cout << "ptr is non-null\n";

    return 0;
}

/* Accidentally dereferencing null and dangling pointers is one of the most common mistakes

- and is probably the most common reason that C++ programs crash in practice.
- We can detect null pointers, but we can't detect dangling pointers.
- It's the programmer’s responsibility to ensure that all pointers to an object 
  that has just been destroyed are properly set to nullptr.
*/


/* Legacy null pointer literals: 0 and NULL

- In older code, you may see two other literal values:
    ```
    int* ptr { 0 }; // initialize a null pointer
    int* ptr { NULL }; // initialize a null pointer
    ```

- Both 0 and NULL should be avoided in modern C++
    + 0 can be ambiguous which one we intend: integer literal or null pointer literal.
    + NULL is not defined by language standard, and it can be defined as 0, 0L, ((void*)0) or something else.
*/

/* References

- https://www.learncpp.com/cpp-tutorial/null-pointers/
*/