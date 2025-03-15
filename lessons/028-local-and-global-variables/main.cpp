/* Storage duration

- A variable’s storage duration (usually just called duration) determines what rules 
  govern when and how a variable will be created (instantiated) and destroyed. 
  In most cases, a variable’s storage duration directly determines its "lifetime".
- Local variables have "automatic storage duration", which means they are created 
  at the point of definition and destroyed at the end of the block they are defined in.
*/

/* Global variable 

- Variables declared outside of a function are global variables.
- visible from the point of declaration until the end of the "file" in which they are declared.
- Global variables can also be defined inside a user-defined namespace.
*/

/* Global variables have static duration

- Global variables are created when the program starts (before main() begins execution), and destroyed when the program ends. 
- This is called "static duration". Variables with static duration are sometimes called "static variables".
*/

#include <iostream>

int g_x { 10 }; // global variable g_x

void changeG()
{
    g_x = 3;
}

namespace Foo // Foo is defined in the global scope
{
    int g_x { 7 }; // g_x is now inside the Foo namespace, but is still a global variable
}

int main()
{
    int x { 2 }; // local variable, no linkage

    {
        int x { 3 }; // this declaration of x refers to a different object than the previous x
        std::cout << x << '\n'; // prints 3
    } // x is destroyed here

    std::cout << x << '\n'; // prints 2

    changeG();
    std::cout << g_x << '\n'; // prints 3

    // Accessing global variable g_x from the Foo namespace
    std::cout << Foo::g_x << '\n'; // prints 7
    std::cout << g_x << '\n'; // prints 3

    return 0;
}

/* Best practice

- Prefer defining global variables inside a namespace rather than in the global namespace.
- Consider using a “g” or “g_” prefix when naming global variables.
*/

/* References

- https://www.learncpp.com/cpp-tutorial/local-variables/
- https://www.learncpp.com/cpp-tutorial/introduction-to-global-variables/
- https://www.learncpp.com/cpp-tutorial/variable-shadowing-name-hiding/
*/