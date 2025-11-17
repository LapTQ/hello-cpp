
/* R-value references

- r-value reference is a reference that is designed to be initialized with an r-value
- an r-value reference is created using `&&` syntax
- R-values references cannot be initialized with l-values.

Properties:
- r-value references extend the lifespan of the object the are initialized with to the lifespan of the r-value references.
- non-const r-value references allow you to modify the r-value.
*/

#include <iostream>

void func1()
{
    int x{ 5 };
    int& lref{ x }; // l-value reference
    int&& rref{ 5 }; // r-value reference

    std::cout << rref << '\n';
}


/* R-value references as function parameters

- you can have overloaded functions for l-values and r-values

- Why would you ever want to do this?  it’s an important part of move semantics that 
  we’ll cover in a later lesson.
*/

void func2(int& x)
{
    std::cout << "l-value reference" << '\n';
}

void func2(int&& x)
{
    std::cout << "r-value reference" << '\n';
}

void func3()
{
    int x{ 5 };
    func2(x); // print "l-value reference"
    func2(5); // print "r-value reference"
}


/* Rvalue reference variables are lvalues

- when used in an expression, r-value reference variables are lvalues. 
    (Just like int x is an lvalue of type int, int&& x is an lvalue of type int&&).
*/

void func4()
{
    int&& ref{ 5 }; // r-value reference
    func2(ref); // print "l-value reference"!!!
}


/* You should almost never return an r-value reference

- ... for the same reason you should almost never return an l-value reference
- In most cases, you’ll end up returning a hanging reference when the referenced object goes out of scope.
*/


int main()
{
    return 0;
}



/* References

- https://www.learncpp.com/cpp-tutorial/rvalue-references/
*/