#include <cstdlib> // for EXIT_SUCCESS and EXIT_FAILURE
#include <iostream>


void printValues(int x, int y)  // copy-initialization, pass by value
{
    std::cout << x << '\n';
    std::cout << y << '\n';
}

void doSomething(int) // ok: unnamed parameter will not generate warning
{
}


int main()
{
    std::cout << EXIT_SUCCESS << ", " << EXIT_FAILURE << '\n';

    printValues(6, 7);

    return 0;
}


/* Nested functions are not supported in C++.
*/

/* Return value of the main function.

- main() is required to return an int.
- The return value from main() is sometimes called a status code.
- The C++ standard only defines the meaning of 3 status codes: 0, EXIT_SUCCESS, and EXIT_FAILURE.
    + 0 and EXIT_SUCCESS both mean the program executed successfully. 
    + EXIT_FAILURE means the program did not execute successfully.
    + EXIT_SUCCESS and EXIT_FAILURE are preprocessor macros defined in the <cstdlib> header.

-  A value-returning function that does not return a value:
    + if main(): implicitly return 0.
    + if user-defined function: might cause undefined behavior. Compiler might not be able to 
      detect you forgot to return a value in some complicated cases.
*/

/* Unnamed parameter

- In a function definition, the name of a function parameter is optional. 
  Therefore, in cases where a function parameter needs to exist but is not used 
  in the body of the function, you can simply omit the name.
*/

/* 
- https://www.learncpp.com/cpp-tutorial/introduction-to-functions/
- https://www.learncpp.com/cpp-tutorial/function-return-values-value-returning-functions/
- https://www.learncpp.com/cpp-tutorial/void-functions-non-value-returning-functions/
- https://www.learncpp.com/cpp-tutorial/introduction-to-function-parameters-and-arguments/
*/