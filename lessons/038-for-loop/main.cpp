/* For loop

for (init-statement; condition; end-expression)
   statement;

The order of execution:
1. Init-statement: only happens once when the loop is initiated.
2. Condition: with each loop iteration, the condition is evaluated. If this evaluates to true, the statement is executed.
3. Loop body: the statement is executed.
4. End-expression: executed after the statement, then jumps back to condition
*/

#include <iostream>

int main()
{
    // example 1
    for (int i{ 0 }; i <= 10; i += 2) // increment by 2 each iteration
        std::cout << i << ' ';

    // example 2, Omitted expressions
    int i{ 0 };
    for ( ; i < 10; ) // no init-statement or end-expression
    {
        std::cout << i << ' ';
        ++i;
    }

    // example 3, Infinite loop
    for ( ; ; ) // infinite loop
    {
        std::cout << "Enter 'q' to quit: ";
        char c{};
        std::cin >> c;

        if (c == 'q')
            break;
    } // equivalent to while (true)

    // example 4, multiple counters
    for (int x{ 0 }, y{ 9 }; x < 10; ++x, --y)
        std::cout << x << ' ' << y << '\n';

    return 0;
}

/* Variables used only inside a loop should be defined inside the loop

- New programmers often think that creating variables is expensive.
- However, creating a variable has no cost.
- it is the initialization that has a cost, and there is typically 
  no cost difference between initialization and assignment. 
*/

/* References

- https://www.learncpp.com/cpp-tutorial/for-statements/
*/