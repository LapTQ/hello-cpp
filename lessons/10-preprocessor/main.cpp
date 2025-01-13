/*
- When you compile your project, prior to compilation, each code (.cpp) file goes through a preprocessing phase.
- When the preprocessor has finished processing a code file, the result is called a translation unit. This translation unit 
  is what is then compiled by the compiler.
- The entire process of preprocessing, compiling, and linking is called translation.
*/

/* Preprocessor directives
- When the preprocessor runs, it scans through the code file (from top to bottom), looking for "preprocessor directives".
- Preprocessor directives (often just called directives) are instructions that start with a # symbol and end with a newline (NOT a semicolon).

- As an aside..., using-directives are not preprocessor directives (and thus are not processed by the preprocessor).
  So while the term directive usually means a preprocessor directive, this is not always the case.
*/

/* #Include
- When you #include a file, the preprocessor replaces the #include directive with the contents of the included file.
- Each translation unit typically consists of a single code (.cpp) file and all header files it #includes (applied recursively).
*/

/* Macro defines
- the #define directive is used to define a macro. A macro is a fragment of code which has been given a name.
- There are two basic types of macros: object-like macros, and function-like macros.


++ Object-like macros with substitution text
- Example:
#define MY_NAME "Alex"
- used (in C) as a way to assign names to literals. This is no longer necessary, as better methods are available in C++.
- Object-like macros with substitution text are now mostly seen in legacy code, and we recommend avoiding them whenever possible.


++ Object-like macros without substitution text
- Example:
#define USE_YEN
- most further occurrences of the identifier is removed and replaced by nothing! 
- This might seem pretty useless, and it is useless for doing text substitution. 
- However, that’s not what this form of the directive is generally used for: Conditional compilation
- Unlike object-like macros with substitution text, macros of this form are generally considered acceptable to use.
*/

#include <iostream>

#define PRINT_JOE

int main()
{
#ifdef PRINT_JOE
    std::cout << "Joe\n"; // will be compiled since PRINT_JOE is defined
#endif

#ifdef PRINT_BOB
    std::cout << "Bob\n"; // not compiled
#endif


#ifndef PRINT_ADBC // compiled
    std::cout << "ADBC\n";
#endif


#ifdef PRINT_XYZ // not compiled since directives are resolved from top to bottom 
    std::cout << "XYZ\n";
#endif
#define PRINT_XYZ


    return 0;
}

/*
- #if 0: a common way to comment out a large block of code that contains multi-line comments.
- To temporarily re-enable code that has been wrapped in an #if 0, you can change the #if 0 to #if 1.
*/

/* Macro substitution within other preprocessor commands
- In most cases, macro substitution does not occur when a macro identifier is used within another preprocessor command:

#define FOO 9

#ifdef FOO // This FOO does not get replaced with 9 because it’s part of another preprocessor directive
    std::cout << FOO << '\n'; // This FOO gets replaced with 9 because it's part of the normal code
#endif
*/

/* #include and #define, scope of #defines
- #include directive replaces the #include directive with the content of the included file, an #include can "copy" directives 
  from the included file into the current file. These directives will then be processed in order.

Alex.h:

#define MY_NAME "Alex"

main.cpp:

#include "Alex.h" // copies #define MY_NAME from Alex.h here
#include <iostream>

int main()
{
	std::cout << "My name is: " << MY_NAME << '\n'; // preprocessor replaces MY_NAME with "Alex"

	return 0;
}


- Directives are only valid from the point of definition to the end of the file in which they are defined.
  Directives defined in one file do not have any impact on other files ("unless" they are #included into another file):

function.cpp:

#include <iostream>

void doSomething()
{
#ifdef PRINT
    std::cout << "Printing!\n";
#endif
#ifndef PRINT
    std::cout << "Not printing!\n";
#endif
}

main.cpp:

void doSomething(); // forward declaration for function doSomething()

#define PRINT

int main()
{
    doSomething();      # "Not printing!"
    // Even though PRINT was defined in main.cpp, that doesn’t have any impact on any of the code 
    // in function.cpp (PRINT is only #defined from the point of definition to the end of main.cpp). 

    return 0;
}

*/


/* References
- https://www.learncpp.com/cpp-tutorial/introduction-to-the-preprocessor/
*/