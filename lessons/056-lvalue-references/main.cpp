/* reference

- In C++, a "reference" is an alias for an existing object.
- The object (or function) being referenced is sometimes called the "referent".

- References aren’t objects. 
- A reference is not required to exist or occupy storage. 
  If possible, the compiler will optimize references away by replacing all occurrences of a reference with the referent.
  However, this isn’t always possible, and in such cases, references may require storage.
- you can’t have a reference to a reference.

- reference is not always identical to the object it is bound to
*/

/* lvalue reference

- An "lvalue reference" acts as an alias to an existing lvalue.
- We can read or modify the value of the object being referenced
  using a non-const reference to it.
*/

/* Nomenclature (attention!!!)

- An lvalue reference to a non-const is commonly just called:
    - "lvalue reference to non-const"
    - "non-const lvalue reference"
    - "lvalue reference" (!!!)
- An lvalue reference to a const is commonly just called:
    - "lvalue reference to const"
    - "const lvalue reference"
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


/* Lvalue references to const

- using the `const` keyword when declaring an lvalue reference.
- treat the object it is referencing as const.

- Lvalue references to const can also bind to modifiable lvalues.
  In such a case, the object being referenced is treated as const when "accessed through the reference".
*/


/* Initializing an lvalue reference to const with an rvalue

- When this happens, a temporary object is created and initialized with the rvalue, 
  and the reference to const is bound to that temporary object.

You might wonder: Temporary objects are normally destroyed at the end of the expression in which they are created,
   so would the reference be left dangling?
- To avoid dangling references in such cases, C++ has a special rule: When a const lvalue reference is "directly" 
  bound to a temporary object, the lifetime of the temporary object is extended to match the lifetime of the reference.
*/


/* Initializing an lvalue reference to const with a value of a different type

- the compiler will create a temporary object of the same type as the reference, 
  initialize it using the value, and then bind the reference to the temporary.
=> this is an example of case when reference is not identical to the object it is bound to.
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
    // int& invalidRef;   // error: references must be initialized
    // const int y { 5 };
    // int& invalidRef { y };  // invalid: non-const lvalue reference can't bind to a non-modifiable lvalue
    // int& invalidRef2 { 0 }; // invalid: non-const lvalue reference can't bind to an rvalue

    
    // References can’t be reseated 
    int x2 { 5 };
    int y2 { 6 };
    int& ref2 { x2 }; // ref is now an alias for x2
    ref2 = y2; // doesn't change reference, instead assigns 6 (the value of y2) to x2
    std::cout << x2 << '\n'; // 6


    // Lvalue reference to const
    const int x3 { 5 };
    const int& ref_x3 { x };
    int y3 { 6 };  // modifiable lvalue
    const int& ref_y3 { y3 };
    // ref_y3 = 7; // error: ref_y3 is const, so we can't modify the value of y3 through ref_y3
    std::cout << y3 << ref_y3 << '\n'; // 66
    y3 = 7;     // modification reflected in ref_y3, because ref_y3 is bound to y3
    std::cout << y3 << ref_y3 << '\n'; // 77


    // Initializing an lvalue reference to const with an rvalue
    const int& ref_rvalue { 5 }; // okay: a temporary object is created and initialized with the rvalue, ref_rvalue is bound to that temporary object


    // Initializing an lvalue reference to const with a value of a different type
    const double& r1 { 5 };
    std::cout << r1 << '\n'; // prints 5
    char c { 'a' };
    const int& r2 { c };     
    std::cout << r2 << '\n'; // prints 97
    short s { 6 };
    const int& r3 { s };
    s--;          // modification not reflected in r3, because r3 is bound to a temporary copy
    std::cout << s << r3 << '\n'; // 56

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/lvalue-references/
- https://www.learncpp.com/cpp-tutorial/lvalue-references-to-const/
*/