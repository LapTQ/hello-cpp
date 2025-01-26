/*
- if-statement or switch-statement: conditional jump
- goto-statement: unconditional jump, through use of a "statement label".
*/


/* Statement labels have function scope

- The goto statement and its corresponding statement label must appear in the same function.

- if you jump forward, you can’t jump forward over the initialization of any variable 
  that is still in scope at the location being jumped to.
*/


#include <iostream>
#include <cmath> // for sqrt() function

int main()
{
    double x{};

tryAgain: // this is a statement label
    std::cout << "Enter a non-negative number: ";
    std::cin >> x;

    if (x < 0.0)
        goto tryAgain; // this is the goto statement

    std::cout << "The square root of " << x << " is " << std::sqrt(x) << '\n';

    
    // can jump forward
    bool skip{ true };
    if (skip)
        goto end; // jump forward; statement label 'end' is visible here due to it having function scope

    std::cout << "cats\n";
end:
    ; // statement labels must be associated with a statement


    // can’t jump forward over an initialization
    goto skip;   // error: this jump is illegal because...
    int x { 5 }; // this initialized variable is still in scope at statement label 'skip'
skip:
    x += 3;      // what would this even evaluate to if x wasn't initialized?
    return 0;
}

/* Avoid using goto

- One notable exception is when you need to exit a nested loop 
  but not the entire function -- in such a case, a goto to just beyond the loops 
  is probably the cleanest solution.
*/

/* References

- https://www.learncpp.com/cpp-tutorial/goto-statements/
*/