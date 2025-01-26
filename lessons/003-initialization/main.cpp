#include<iostream>

int main() 
{
    int width;
    width = 5; // copy-assignment

    [[maybe_unused]] int w0 { 6 }; // initialization
    /* Unlike assignment (which is comparably simple), initialization in C++ is complex 
    
    There are 5 commonly used ways to initialize variables in C++:
    */
    [[maybe_unused]] int a;         // default-initialization (no initializer)
    // Traditional
    [[maybe_unused]] int b = 5;     // copy-initialization (initial value after equals sign)
    [[maybe_unused]] int c ( 6 );   // direct-initialization (initial value in parenthesis)
    // Modern (preferred)
    [[maybe_unused]] int d { 7 };   // direct-list initialization (initial value in braces)
    [[maybe_unused]] int f {};      // value-initialization (empty braces)

    /* default-initialization
    * Unlike some programming languages, C/C++ does not automatically initialize in default-initialization.
      In this case, default-initialization performs no actual initialization. the default value of that 
      variable is whatever (garbage) value happens to already be in that memory address!
    
    * ALWAYS initialize your variables:
      + For example, the standard may say, “you must do X before Y”, but a compiler author may feel
        that’s unnecessary, and make Y work even if you don’t do X first. An uninitialized variable
        might cause "undefined behavior".

    */

    /* copy-initialization
    * This form of initialization was inherited from the C language.
    
    - less efficient than other forms of initialization for some complex types.
    - can be hard to differentiate from copy-assignment.
    + However, C++17 remedied the bulk of these issues, and copy-initialization is now finding new advocates.
    */

    /* direct-initialization
    * initially introduced to allow for more efficient initialization of complex objects

    - fallen out of favor in modern C++, largely due to being superseded by direct-list-initialization.
    - can be hard to differentiate variables from functions.
    + However, direct-list-initialization has a few quirks of its own, and so direct-initialization is once again finding use in certain cases.
    */

    /* Direct-list-initialization and Copy-list-initialization
    
    int width { 5 };    // direct-list-initialization (preferred)
    int height = { 6 }; // copy-list-initialization (rarely used)
    
    * Prior to the introduction of list-initialization, some types of initialization required using copy-initialization, and other types of initialization required using direct-initialization.
      List-initialization was introduced to provide a consistent initialization syntax (which is why it is sometimes called “uniform initialization”)
    */

    // List-initialization disallows narrowing conversions
    [[maybe_unused]] int w1 { 4.5 }; // compile error: list init does not allow narrowing conversion of 4.5 to 4
    [[maybe_unused]] int w2 = 4.5;   // compiles: copy-init initializes width with 4
    [[maybe_unused]] int w3(4.5);    // compiles: direct-init initializes width with 4

    return 0;
}