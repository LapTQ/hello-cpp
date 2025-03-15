/* Using-declarations

- One way to reduce the repetition of typing std:: over and over is to utilize a using-declaration statement.
- it allows us to use an unqualified name as an alias for a qualified name.
*/

/* Using-directives 

using namespace std; 

- should be avoided.
*/

/* The scope of using-statements

- If a using-declaration or using-directive is used within a block, the names are applicable to just that block.
*/

/* Do not use using-statements in header files, or before an #include directive

- But what about using-statements within functions defined inside header files? => NO (for the same reason that we shouldn’t use using-statements before an #include directive.!!!!
  See example below
*/

#include <iostream>

#include "FooDouble.h"

using Foo::print; // we moved the using-statement here, before the #include directive
#include "FooInt.h"

int main()
{
   using std::cout; // this using declaration tells the compiler that cout should resolve to std::cout
   cout << "Hello world!\n"; // so no std:: prefix is needed here!

   // avoid using-directives before #include directive
   print(5);  // Calls Foo::print(double). This example uses a concept we haven’t covered yet called “function overloading”

   return 0;
} // the using-declaration expires at the end of the current scope

/* References

- https://www.learncpp.com/cpp-tutorial/using-declarations-and-using-directives/
*/