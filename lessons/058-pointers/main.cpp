/*

- In fact, pointers behave a lot like lvalue references.
*/


/* address-of operator (&)

- For objects that use more than one byte of memory, address-of will 
  return the memory address of the first byte used by the object.

The & symbol tends to cause confusion because it has different meanings depending on context:
- When following a type name, & denotes an lvalue reference: int& ref.
- When used in a unary context in an expression, & is the address-of operator: std::cout << &x.
- When used in a binary context in an expression, & is the Bitwise AND operator: std::cout << x & y.
*/

/* dereference operator (*)

- access the object stored at an address. It returns an lvalue.
*/

/* Pointer

- A pointer is an object that holds a memory address (typically of another variable) as its value.

- pointer types are declared using an asterisk (*):
    int; // normal int
    int&; // lvalue reference
    int*; // pointer

- Warning, the asterisk has to be included with each variable:
    int* x, y; // incorrect
    int* x, * y; // correct
  you generally should not declare multiple variables on a single line.
*/

/* Pointer initialization

- Like normal variables, pointers are not initialized by default.
  
- A pointer that has not been initialized is sometimes called a wild pointer.
  Wild pointers contain a garbage address, and dereferencing a wild pointer will result in undefined behavior.
  => Always initialize pointers when you declare them.
*/


/* The address-of operator returns a pointer

- The address-of operator (&) does not return a literal.
  Instead, it returns a pointer, whose type is derived from the argument.
*/


/* Pointers and assignment

With pointer, we can:
- change that the pointer points to
- change the value of the object being pointed to
*/


/* Pointers behave much like lvalue references

- pointers and references both provide a way to indirectly access another object.

- The primary difference:
  ++ with pointer, we need to explicitly get address-of and dereference.
     with reference, the address-of and dereference happens implicit.
  ++ references must be initialized, while pointers do not.
  ++ references are not objects, while pointers are.
  ++ references can not be reassigned, while pointers can.
  ++ references must always be bound to an object, while pointers point to nothing.
  ++ references are safe (outside of dangling references), while pointers can be dangerous.
*/


#include <iostream>

int main()
{
    int x{ 5 };
    std::cout << &x << '\n'; // address-of operator (&), print 0x7ffd4717a684
    std::cout << *(&x) << '\n'; // dereference operator (*), print 5

    // pointer
    int* ptr; // an uninitialized pointer (holds a garbage address)
    int* ptr2{};     // a null pointer (we'll discuss these in the next lesson)
    int* ptr3{ &x }; // a pointer initialized with the address of variable x
    // the address-of operator (&) returns a pointer

    std::cout << *ptr3 << '\n'; // dereference, print 5


    // Pointers and assignment
    int y{ 7 };
    ptr3 = &y; // change what ptr3 points to
    std::cout << *ptr3 << '\n'; // dereference, print 7

    *ptr3 = 10; // change the value of the object being pointed to, *ptr3 is an lvalue
    std::cout << y << '\n'; // print 10


    // Pointers behave much like lvalue references
    int& ref { x };  // get a reference to x
    ptr = &x; // get a pointer to x

    std::cout << x;
    std::cout << ref;  // use the reference to print x's value (5)
    std::cout << *ptr << '\n'; // use the pointer to print x's value (5)

    ref = 6; // use the reference to change the value of x
    std::cout << x;
    std::cout << ref;  // use the reference to print x's value (6)
    std::cout << *ptr << '\n'; // use the pointer to print x's value (6)

    *ptr = 7; // use the pointer to change the value of x
    std::cout << x;
    std::cout << ref;  // use the reference to print x's value (7)
    std::cout << *ptr << '\n'; // use the pointer to print x's value (7)


    return 0;
}


/* The size of pointers

- dependent upon the architecture.
- a pointer on a 32-bit machine is 32 bits (4 bytes). 
  With a 64-bit executable, a pointer would be 64 bits.
- The size of the pointer is always the same.
*/


/* References

- https://www.learncpp.com/cpp-tutorial/introduction-to-pointers/
*/