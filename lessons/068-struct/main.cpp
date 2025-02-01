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


/* initialization possibilities

If an aggregate is defined with no initialization list:
- If a default member initializer exists, the default is used.
- If no default member initializer exists, the member remains uninitialized.
If an aggregate is defined with an initialization list:
- If an explicit initialization value exists, that explicit value is used.
- If an initializer is missing and a default member initializer exists, the default is used.
- If an initializer is missing and no default member initializer exists, value initialization occurs.

=> Always provide default values for your members

=> Prefer value initialization over default initialization for aggregates:
    ```
    Fraction f1; // default initialization
    Fraction f2 {}; // value initialization, preferred
    ```
    
    value initialization will protect you from accidentally using uninitialized variables.
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


/* Passing structs (by reference)

Few reminders about passing temporary objects:
- they are created and initialized at the point of definition, 
  and are destroyed at the end of the full expression in which they are created.
- And evaluation of a temporary object is an rvalue expression.
- it will only bind to parameters that accept rvalues.
  This includes pass by value and pass by const reference, 
  and excludes pass by non-const reference and pass by address.
*/

#include <iostream>

void printEmployee(const Employee& employee) // note pass by reference here
{
    std::cout << "ID:   " << employee.id << '\n';
    std::cout << "Age:  " << employee.age << '\n';
    std::cout << "Wage: " << employee.wage << '\n';
}


/* Returning structs

- In the case where the function has an explicit return type, we can 
  even omit the type in the return statement.
*/

Employee dummyEmployee()
{
    return Employee { 1, 32, 60000.0 };
}

Employee dummyEmployee2()
{
    return { 1, 32, 60000.0 };  // can omit the type, implicit conversion
}

Employee dummyEmployee3()
{
    return { };  // value-initialize all members
}


int main()
{
    Employee joe {};
    joe.age = 32; // To access a specific member variable, we use the member selection operator (operator.)


    // Aggregate initialization
    Employee frank = { 1, 32, 60000.0 }; // copy-list initialization using braced list
    Employee alice { 2, 28, 45000.0 };     // list initialization using braced list (preferred)
    // assigment
    alice = { alice.id, 30, 4000.0 };


    // initialization possibilities
    Employee2 pat; // no initialization list => pat.whatever is not initialized
    Employee2 bob { 2, 28 }; // bob.whatever is value-initialized { } to 0.0.


    // Designated initializers (C++20)
    Foo f1 { .a{ 1 }, .c{ 3 } };  // okay, list initialization
    Foo f2 { .a = 1, .c = 3 };    // okay, copy initialization
    // Foo f3{ .b{ 2 }, .a{ 1 } };   // error, order mot match
    // assignment
    f1 = { .a{ 1 }, .c{ 3 } }; 


    // Initializing a struct with another struct of the same type   
    Foo f3 { 1, 2, 3};
    Foo f4 = f3; // copy initialization
    Foo f5 { f3 }; // direct-list initialization
    Foo f6(f3); // direct-initialization


    // Passing structs (by reference)
    printEmployee(Employee { 14, 32, 24.15 }); // temporary objects
    printEmployee({ 14, 32, 24.15 });  //  implicit conversion


    // Returning structs
    printEmployee(dummyEmployee());
    printEmployee(dummyEmployee2());
    printEmployee(dummyEmployee3());
    

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/introduction-to-structs-members-and-member-selection/
- https://www.learncpp.com/cpp-tutorial/struct-aggregate-initialization/
- https://www.learncpp.com/cpp-tutorial/default-member-initialization/
- https://www.learncpp.com/cpp-tutorial/passing-and-returning-structs/
*/

