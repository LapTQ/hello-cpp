/* without a `break` or `return`, execution will overflow into subsequent cases

- The [[fallthrough]] attribute is used to tell the compiler that the fallthrough is intended.
- Unlike if-statement, Labels in switch-statement do not define a new scope.
- the statements after labels are all scoped to the switch block.
*/

/* Declaration is allowed, but initialization is disallowed

- because the switch could jump over the initializer if there is a subsequent case defined, 
  in which case the variable would be undefined
- If a case needs to define and/or initialize a new variable, the best practice is to do so 
  inside an explicit block underneath the case statement
*/

#include <iostream>


// 

int main()
{
    switch (2)
    {
    case 1: // Does not match
        std::cout << 1 << '\n'; // Skipped
    case 2: // Match!
        std::cout << 2 << '\n'; // Execution begins here
        [[fallthrough]]; // intentional fallthrough -- note the semicolon to indicate the null 
    case 3:
        std::cout << 3 << '\n'; // This is also executed
        [[fallthrough]]; // intentional fallthrough -- note the semicolon to indicate the null 
    default:
        std::cout << 5 << '\n'; // This is also executed
    }


    char c { 'a' };
    bool isVowel {};
    // instead of
    isVowel = (c=='a' || c=='e' || c=='i' || c=='o' || c=='u' ||
        c=='A' || c=='E' || c=='I' || c=='O' || c=='U');
    // we can
    switch (c)
    {
    case 'a': // if c is 'a'
    case 'e': // or if c is 'e'
    case 'i': // or if c is 'i'
    case 'o': // or if c is 'o'
    case 'u': // or if c is 'u'
    case 'A': // or if c is 'A'
    case 'E': // or if c is 'E'
    case 'I': // or if c is 'I'
    case 'O': // or if c is 'O'
    case 'U': // or if c is 'U'
        isVowel = true;
    default:
        isVowel = false;
    }


    // initialization is not allowed
    switch (1)
    {
        int a; // okay: definition is allowed before the case labels
        int b{ 5 }; // illegal: initialization is not allowed before the case labels
    case 1:
        int y; // okay but bad practice: definition is allowed within a case
        y = 4; // okay: assignment is allowed
        break;
    case 2:
        int z{ 4 }; // illegal: initialization is not allowed if subsequent cases exist
        y = 5; // okay: y was declared above, so we can use it here too
        break;
    case 3:
        break;
    }

    // but can be done inside an explicit block
    switch (1)
    {
    case 1:
    { // note addition of explicit block here
        int x{ 4 }; // okay, variables can be initialized inside a block inside a case
        std::cout << x;
        break;
    }
    }

    return 0;
}

/* References

- https://www.learncpp.com/cpp-tutorial/switch-fallthrough-and-scoping/
*/