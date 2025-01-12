#include <iostream>

int add(int x, int y); // needed so main.cpp knows that add() is a function defined elsewhere

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';
    return 0;
}

/*
- Remember, the compiler compiles each file individually.
- It does not remember anything it has seen from previously compiled code files.
- This limited visibility and short memory is intentional, for a few reasons:
    + source files of a project can be compiled in any order.
    + When we change a source file, only that source file needs to be recompiled.
*/