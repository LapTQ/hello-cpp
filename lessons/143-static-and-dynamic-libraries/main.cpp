/*
- A library is a package of code that is reused by many programs.
- Typically, a C++ library comes in two pieces:
    + Header files: expose the library’s functionality to the program.
    + Binary files: contain the compiled implementation of the library’s functionality.
*/


/*
There are two types of libraries:

- Static libraries (also known as an archive): are linked directly into the program.
    When you compile a program that uses a static library, the library becomes part of your executable.
    On Windows: .lib files. On Linux: .a files.
- Dynamic libraries (also known as shared libraries): loaded into your program at runtime.
    When you compile a program that uses a dynamic library, the library is not included in your executable.
    On Windows: .dll files. On Linux: .so files.

- Import libraries: Because dynamic libraries are not linked into your program, you need to explicitly load them.
    An import library is a static library that automatically loads the dynamic library, and is linked into your program at compile time.
    Then, the dynamic library can be used as if it were a static library.
    On Linux, .so files works as both dynamic and import libraries. Most linkers can build an import library for a dynamic library.
    when the dynamic library is created.
*/


/* Installing and using libraries

4 steps:

1. Acquire the library: The best option is to download a precompiled package, or if it does not exists, you can download the source code and compile it yourself.
2. Install the library: 
3. Make sure the compiler knows where to look for the header file(s) for the library. 
   On Linux, header files are typically installed to /usr/include.
4. Tell the linker where to look for the library file(s).
    On Linux, library files are typically installed to /usr/lib.
5. If using static libraries or import libraries, tell the linker which library files to link.
6. #include the library’s header file(s).
7. If using dynamic libraries, make sure the program knows where to find them.
    On Linux, library are typically installed to /usr/lib which is included in the LD_LIBRARY_PATH environment variable.
*/


/* References

- https://www.learncpp.com/cpp-tutorial/a1-static-and-dynamic-libraries/
*/