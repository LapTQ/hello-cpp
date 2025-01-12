#include <iostream>

int add(int x, int y); // function prototype (forward declaration)
/* It is worth noting that function declarations do not need to specify the names of the parameters:

int add(int, int); // function prototype (forward declaration)

*/

int main()
{
    std::cout << add(4, 5) << '\n'; // call the function

    return 0;
}

int add(int x, int y) // function definition
{
    return x + y;
}


/* Forward declaration 

- allows us to tell the compiler about the existence of an identifier before actually defining the identifier.
- to do so, we use a ***function declaration*** statement (also called a ***function prototype***).

*/

/* Declarations vs. definitions

- Declaration: tells the compiler about the existence of an identifier.
- Definition: actually implements (for functions and types) or instantiates (for variables) the identifier.

- In C++, all definitions are declarations. Therefore int x; is both a definition and a declaration.
- However, not all declarations are definitions. Declarations that are not definitions are called *pure declarations*.

*/