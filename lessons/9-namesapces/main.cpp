// An example of name collision: a.cpp and main.cpp

#include <iostream>

void myFcn(int x)
{
    std::cout << 2 * x;
}

int main()
{
    return 0;
}

/* Naming collision (or naming conflict)
- If the colliding identifiers are introduced into the same file, the result will be a compiler error. 
- If the colliding identifiers are introduced into separate files belonging to the same program, the result will be a linker error.
- When the compiler compiles this program, it will compile a.cpp and main.cpp independently, and each file will compile with no problems.
  However, when the linker executes, it will link all the definitions in a.cpp and main.cpp together, and discover conflicting definitions for function myFcn().
*/

/* Scope regions
- A scope region is an area of source code where all declared identifiers are considered distinct from names declared in other scopes.
- Within a given scope region, all identifiers must be unique.
- The body of a function is one example of a scope region. if you try to define two identically-named identifiers within the same function, a naming collision will result.
*/

/* Namespaces
- A namespace provides another type of scope region (called namespace scope).
- Any names declared inside the namespace won’t be mistaken for identical names in other scopes.

- Only declarations and definitions can appear in the scope of a namespace (not executable statements). 
  However, a function can be defined inside a namespace, and that function can contain executable statements.
*/

/* Global namespace
- In C++, any name that is not defined inside a class, function, or a namespace is considered to be part of 
  an implicitly-defined namespace called the global namespace (sometimes also called the global scope).
- In the example at the top of the lesson, functions main() and both versions of myFcn() are defined inside the global namespace.
*/

/* The std namespace
- When C++ was originally designed, all of the identifiers in the C++ standard library (including std::cin and std::cout) 
  were available to be used without the std:: prefix (they were part of the global namespace).
- However, this meant that any identifier in the standard library could potentially conflict with any name you picked for your 
  own identifiers (also defined in the global namespace).
- So C++ moved all of the functionality in the standard library into a namespace named std (short for “standard”).
*/

/* Explicit namespace qualifier
- The :: symbol is an operator called the scope resolution operator.
- When an identifier includes a namespace prefix, the identifier is called a qualified name.
*/

/* Using namespace std (and why to avoid it)
- Another way to access identifiers inside a namespace without using a namespace prefix is to use a using-directive statement.

using namespace std;

- However, used in this way, this is a bad practice, and highly discouraged:

#include <iostream> // imports the declaration of std::cout into the global scope

using namespace std; // makes std::cout accessible as "cout"

int cout() // defines our own "cout" function in the global namespace
{
    return 5;
}

int main()
{
    cout << "Hello, world!"; // Compile error!  Which cout do we want here?  The one in the std namespace or the one we defined above?

    return 0;
}

*/