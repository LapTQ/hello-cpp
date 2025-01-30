/* reference

- In C++, a "reference" is an alias for an existing object.
- The object (or function) being referenced is sometimes called the "referent".

- References aren’t objects. 
- A reference is not required to exist or occupy storage. 
  If possible, the compiler will optimize references away by replacing all occurrences of a reference with the referent.
  However, this isn’t always possible, and in such cases, references may require storage.
- you can’t have a reference to a reference.
*/

/* lvalue reference

- An "lvalue reference" acts as an alias to an existing lvalue.
- We can read or modify the value of the object being referenced
  using a non-const reference to it.
*/

/* reference type

- A "reference type" is a type that specifies a reference.
  For example: int& is the type of an lvalue reference to an int object
*/

/* Reference initialization

- all references "must" be initialized, using a form of initialization called "reference initialization".
- When a reference is initialized with an object (or function), we say it is "bound" to that object (or function).
  Such process is called "reference binding".
- Once initialized, references can’t be reseated (changed to refer to another object)
- Non-const lvalue references can only be bound to a modifiable lvalue.
*/

/* In most cases, a reference will only bind to an object whose type matches the referenced type
*/

/* Reference variables follow the same scoping and duration rules that normal variables do
*/

/* Dangling references

- When an object being referenced is destroyed before a reference to it, the reference is left 
  referencing an object that no longer exists. Such a reference is called a "dangling reference".
- Accessing a dangling reference leads to undefined behavior.
*/

#include <iostream>

int main()
{
    int x { 5 };    // x is a normal integer variable
    int& ref { x }; // ref is an lvalue reference variable that can now be used as an alias for variable x
    int& reff { ref }; // reff bound to x, not to ref because ref evaluate to x
    // From the compiler’s perspective, it doesn’t matter whether you write `int& ref` or `int &ref`.

    std::cout << x << '\n';  // print the value of x (5)
    std::cout << ref << '\n'; // print the value of x via ref (5)

    
    // modify value using references
    ref = 6;
    std::cout << x << ref << '\n';
    x = 7;
    std::cout << x << ref << '\n';

    
    // Reference initialization
    int& invalidRef;   // error: references must be initialized
    const int y { 5 };
    int& invalidRef { y };  // invalid: non-const lvalue reference can't bind to a non-modifiable lvalue
    int& invalidRef2 { 0 }; // invalid: non-const lvalue reference can't bind to an rvalue

    
    // References can’t be reseated 
    int x2 { 5 };
    int y2 { 6 };
    int& ref2 { x2 }; // ref is now an alias for x2
    ref2 = y2; // doesn't change reference, instead assigns 6 (the value of y2) to x2
    std::cout << x2 << '\n'; // 6

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/lvalue-references/
*/