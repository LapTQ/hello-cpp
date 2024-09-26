#include <iostream>

int main()
{
    std::cout << "Here is some text.";
    return 0;
}

/*
Compiling your source code:
    The compiler translates your C++ code into machine language instructions. 
    These instructions are stored in an intermediate file called an object file.
    The object file also contains metadata that is required in subsequent steps.
    If your program had 3 .cpp files, the compiler would generate 3 object files (.o or .obj), typically witht the same name with the .cpp file.
Linking object files and libraries:
    After the compiler has successfully finished, another program called the linker kicks in.
    The linker’s job is to combine all of the object files and produce the desired output file (typically an executable file).
    The linker:
        - ensures all cross-file dependencies are resolved properly
        - linking library files. A library file is a collection of precompiled code that has been “packaged up” for reuse in other programs.
            C++ comes with an extensive library called the C++ Standard Library. 
            One of the most commonly used parts of the C++ standard library is the Input/Output library (often called “iostream”).
            Most C++ linkers are configured to link in the standard library by default.
            You can also optionally link other libraries. You can download a library that already knew how to do those things, and use that.
Building:
    Because there are multiple steps involved, the term "building" is used to refer to the full process of converting source code files into an executable that can be run. 
*/