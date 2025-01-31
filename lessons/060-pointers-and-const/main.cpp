/* Pointer to const

- A "pointer to const" treats the value being pointed to as constant, 
  regardless of whether the object at that address was initially defined as const or not.
- A pointer to const "can" change what it points to.

- Create a pointer to const:
    ```
    const int* ptr { ... }; // const keyword before the data type
    ```
*/


/* Const pointers

- A const pointer is a pointer whose address can not be changed after initialization.

- Create a const pointer:
    ```
    int* const ptr { ... }; // const keyword after the data type
    ```
*/


/* Const pointer to a const value

- A const pointer to a const value can not have its address changed, 
  nor can the value it is pointing to be changed through the pointer.

- Create a const pointer to a const value:
    ```
    const int* const ptr { ... }; // const keyword before and after the data type
    ```
*/


#include <iostream>

int main()
{
    const int x { 5 }; // x is now const
    int* ptr { &x };   // compile error: a normal pointer can't point to a const value

    // pointer to const
    const int* ptr2 { nullptr };
    int y { 6 };
    ptr2 = &y; // okay: a pointer to const can point to a non-const value
    const int z { 7 };
    ptr2 = &z; // okay: a pointer to const can point to a const value
               // okay, can change what it points to

    *ptr2 = 8; // compile error: a pointer to const can't change the value it points to
    

    // const pointer
    int a { 5 };
    int* const ptr3 { &a }; // a const pointer
    ptr = &y; // compile error: a const pointer can't change what it points to
    *ptr3 = 6; // okay: a const pointer can change the value it points to
    std::cout << a << '\n'; // print 6


    // const pointer to a const value
    const int b { 5 };
    const int* const ptr4 { &b }; // a const pointer to a const value

    return 0;
}

/* References

- https://www.learncpp.com/cpp-tutorial/pointers-and-const/
*/