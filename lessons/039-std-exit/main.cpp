/* normal termination
- std::exit() is a function that causes the program to "terminate normally".
- Note that the term normal termination does NOT imply anything about whether the program was "successful".
- For example, your program would probably return a non-zero status code 
  to indicate the "failure" state, but it would STILL have a normal termination.

*/

/*
- std::exit() is called implicitly after function main() returns.

- std::exit() performs a number of cleanup functions. 
  First, objects with static storage duration are destroyed. 
  Then some other miscellaneous file cleanup is done if any files were used.
- std::exit() does not clean up local variables.
*/

/* Why bother cleaning up on exit?

- When an application exits, modern OSes will generally clean up any memory that the application 
  does not properly clean up itself. 
- This leads to the question, “so why bother doing cleanup on exit?”. 

There are (at least) two reasons:
- a “good habit” that you will need to use to avoid memory leaks.
- There are other kinds of cleanup that may be necessary for your program to behave predictably. 
  For example, if you write data to a file and then unexpectedly exit, 
  that data may not have been flushed to the file yet.
*/

/* std::atexit

- Because std::exit() terminates the program immediately, you may want to 
  manually do some cleanup before terminating (e.g. closing files, writing logs, etc.).

- std::atexit allows you to specify a function that will automatically be called on program termination via std::exit().

- the function being registered must take no parameters and have no return value.
- you can register multiple cleanup functions, and they will be called in the reverse order they were registered.
*/

#include <cstdlib> // for std::exit()
#include <iostream>

void cleanup()
{
    // code here to do any kind of cleanup required
    std::cout << "cleanup!\n";
}

int main()
{
    // register cleanup() to be called automatically when std::exit() is called
    std::atexit(cleanup);

    std::cout << 1 << '\n';

    std::exit(0); // terminate and return status code 0 to operating system

    // The following statements never execute
    std::cout << 2 << '\n';

    return 0;
}

/* std::abort and std::terminate

- The std::abort() function causes your program to terminate "abnormally".
  For example, dividing by 0 will result in an abnormal termination. 
- std::abort() does not do any cleanup.

- The std::terminate() function is typically used in conjunction with exceptions.
- often called implicitly when an exception isn’t handled.
- By default, std::terminate() calls std::abort().
*/

/* References

- https://www.learncpp.com/cpp-tutorial/halts-exiting-your-program-early/
*/