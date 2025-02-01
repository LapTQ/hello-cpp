/* Struct

- A struct is a class type (as are classes and unions). 
  As such, anything that applies to class types applies to structs.
*/

struct Employee
{
    // data members (or member variables)
    int id {};
    int age {};
    double wage {};
};


/* Aggregate initialization

- In general programming, an "aggregate data type" (also called an "aggregate") is 
  any type that can contain multiple data members. 

- To directly initialize the members of aggregates, we provide an initializer list as an initializer:
  There are 2 primary forms of aggregate initialization:
    ```
    Employee frank = { 1, 32, 60000.0 }; // copy-list initialization using braced list
    Employee joe { 2, 28, 45000.0 };     // list initialization using braced list (preferred)
    ```
  
  Each of these initialization forms does a memberwise initialization.
  each member in the struct is initialized in the order of declaration.
*/


/* Missing initializers in an initializer list

- each member without an explicit initializer is initialized as follows:
  + If the member has a default member initializer, that is used.
  + Otherwise, the member is value-initialized.
*/

struct Employee2
{
    int id {};
    int age {};
    double wage { 76000.0 }; 
    double whatever;
};


/* Const structs

- Variables of a struct type can be const (or constexpr), and just like all const variables, they must be initialized.
*/


/* Designated initializers (C++20)

- consider what would happen if you add a new member to an existing struct that is not the last member:
    ```
    Foo f { 1, 3 }; // all your initialization values have shifted
    ```

To help avoid this, C++20 introduces designated initializers. 
(The members must be initialized in the same order in which they are declared in the struct.)


- Prefer adding new member to the bottom of the definition list over designated initializers.
*/

struct Foo
{
    int a {};
    int b {}; // just added
    int c {};
};


/* Initializing a struct with another struct of the same type
*/


#include <iostream>

int main()
{
    Employee joe {};
    joe.age = 32; // To access a specific member variable, we use the member selection operator (operator.)


    // Aggregate initialization
    Employee frank = { 1, 32, 60000.0 }; // copy-list initialization using braced list
    Employee alice { 2, 28, 45000.0 };     // list initialization using braced list (preferred)
    // assigment
    alice = { alice.id, 30, 4000.0 };


    // Missing initializers in an initializer list
    Employee2 bob { 2, 28 }; // bob.whatever is value-initialized { } to 0.0.


    // Designated initializers (C++20)
    Foo f1 { .a{ 1 }, .c{ 3 } };  // okay, list initialization
    Foo f2 { .a = 1, .c = 3 };    // okay, copy initialization
    Foo f3{ .b{ 2 }, .a{ 1 } };   // error, order mot match
    // assignment
    f1 = { .a{ 1 }, .c{ 3 } }; 


    // Initializing a struct with another struct of the same type   
    Foo f3 { 1, 2, 3};
    Foo f4 = f3; // copy initialization
    Foo f5 { f3 }; // direct-list initialization
    Foo f6(f3); // direct-initialization

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/introduction-to-structs-members-and-member-selection/
- https://www.learncpp.com/cpp-tutorial/struct-aggregate-initialization/
*/

