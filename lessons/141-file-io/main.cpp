/*
There are 3 basic file I/O classes in C++:
    + ifstream: input
    + ofstream: output
    + fstream: input/output 
*/


/* File output

- there are several ways to close a file: 
    + explicitly call the close() function, 
    + or just let the file I/O variable go out of scope

- Output in C++ may be buffered. One way to cause the buffer to be flushed is to close the file.
    If program terminates immediately (either by crashing, or by calling exit()), the file may not be closed,
    which means the buffer may not be flushed.
    => it's a good idea to explicitly close the file.
*/

#include <fstream>
#include <iostream>

int func1()
{
    std::ofstream outf{ "Sample.txt" };

    // If we couldn't open the output file stream for writing
    if (!outf)
    {
        std::cerr << "Uh oh, Sample.txt could not be opened for writing!\n";
        return 1;
    }

    // We'll write two lines into this file
    outf << "This is line 1\n";
    outf << "This is line 2\n";

    return 0;

    // When outf goes out of scope, the ofstream
    // destructor will close the file
}


/* File input

- ifstream returns a 0 if we’ve reached the end of the file (EOF).
*/

#include <fstream>
#include <iostream>
#include <string>

int func2()
{
    std::ifstream inf{ "Sample.txt" };

    if (!inf)
    {
        std::cerr << "Uh oh, Sample.txt could not be opened for reading!\n";
        return 1;
    }

    std::string strInput{};
    while (inf >> strInput)
        std::cout << strInput << '\n';

    return 0;

    // When inf goes out of scope, the ifstream
    // destructor will close the file
}

#include <fstream>
#include <iostream>
#include <string>

int func3()
{
    std::ifstream inf{ "Sample.txt" };

    if (!inf)
    {
        std::cerr << "Uh oh, Sample.txt could not be opened for reading!\n";
        return 1;
    }

    std::string strInput{};
    while (std::getline(inf, strInput))
	    std::cout << strInput << '\n';

    return 0;
}


/* File mode

Read: io-file-mode.png

- It is possible to specify multiple flags by bitwise ORing them together: |
  e.g., fstream defaults to `std::ios::in | std::ios::out`, meaning that you can read and write to the file.
*/

#include <iostream>
#include <fstream>

int func4()
{
    // ios:app flag to tell the ofstream to append
    std::ofstream outf{ "Sample.txt", std::ios::app };

    if (!outf)
    {
        std::cerr << "Uh oh, Sample.txt could not be opened for writing!\n";
        return 1;
    }

    outf << "This is line 3\n";
    outf << "This is line 4\n";

    return 0;
}


/* Explicitly opening files using open()

- ... iust like it is possible to explicitly close a file stream using close()
*/

#include <iostream>
#include <fstream>

int func5()
{
    std::ofstream outf{};
    outf.open("Sample.txt");

    if (!outf)
    {
        std::cerr << "Uh oh, Sample.txt could not be opened for writing!\n";
        return 1;
    }

    outf << "This is line 5\n";
    outf << "This is line 6\n";

    outf.close();

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/basic-file-io/
*/