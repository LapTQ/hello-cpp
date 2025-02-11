/*
- The memory that a program uses is typically divided into a few different areas, called segments:
    + code segment (text segment): where the compiled program sits in memory
    + bss segment (uninitialized data segment): where zero-initialized global and static variables are stored.
    + data segment (initialized data segment): where initialized global and static variables are stored.
    + heap: where dynamically allocated variables are allocated from.
    + call stack: where function parameters, local variables, and other function-related information are stored.

For this lesson, we’ll focus primarily on the heap and the stack
*/


/* The heap segment

- Allocating memory on the heap is comparatively slow.
*/


/* The call stack

... keeps track of all the active functions (those that have been called but have not yet terminated). 
Here is the sequence of steps that takes place when a function is called:
1. The program encounters a function call.
2. A stack frame is constructed and pushed on the stack. The stack frame consists of:
    - The address of the instruction beyond the function call (called the return address). This is how the CPU remembers where to return to after the called function exits.
    - All function arguments.
    - Memory for any local variables
    - Saved copies of any registers modified by the function that need to be restored when the function returns
3. The CPU jumps to the function’s start point.
4. The instructions inside of the function begin executing.

When the function terminates, the following steps happen:
1. Registers are restored from the call stack
2. The stack frame is popped off the stack. This frees the memory for all local variables and arguments.
3. The return value is handled.
4. The CPU resumes execution at the return address.

All memory allocated on the stack is known at compile time. Consequently, this memory can be accessed directly through a variable.
*/


/* Stack overflow

- The stack has a limited size. On Visual Studio for Windows, the default stack size is 1MB. With g++/Clang for Unix variants, it can be as large as 8MB.
- Stack overflow is generally the result of allocating too many variables on the stack, and/or making too many nested function calls.
- Stack overflow will generally cause your OS to issue an access violation and terminate the program.

Example:
*/

#include <iostream>

int main()
{
    int stack[10000000];
    std::cout << "hi" << stack[0]; // This program tries to allocate a huge (likely 40MB) array on the stack

    return 0;
}    // scripts/compile-and-run.sh: line 100: 11955 Segmentation fault      (core dumped) $path_out

/* References

- https://www.learncpp.com/cpp-tutorial/the-stack-and-the-heap/
*/