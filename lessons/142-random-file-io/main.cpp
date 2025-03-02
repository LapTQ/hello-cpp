/*
- Each file stream class contains a file pointer that is used to keep track of the current read/write position within the file.
- So far, all of the file access we’ve done has been sequential. However, it is also possible to do random file access
  by manipulating the file pointer using either seekg() function (for input) and seekp() function (for output).
- with file streams, the read and write position are always identical, so seekg and seekp can be used interchangeably.

- Two other useful functions are tellg() and tellp(), which return the absolute position of the file pointer. 
*/


#include <iostream>
#include <fstream>


int func1()
{
    std::ifstream inf{ "Sample.txt" };

    if (!inf)
    {
        std::cerr << "Uh oh, Sample.txt could not be opened for reading!\n";
        return 1;
    }

    inf.seekg(14, std::ios::cur); // move forward 14 bytes
    inf.seekg(-18, std::ios::cur); // move backwards 18 bytes
    inf.seekg(22, std::ios::beg); // move to 22nd byte in file
    inf.seekg(24); // move to 24th byte in file
    inf.seekg(-28, std::ios::end); // move to the 28th byte before end of the file
    inf.seekg(0, std::ios::beg); // move to beginning of file
    inf.seekg(0, std::ios::end); // move to end of file


    std::string strData;
    // Get the rest of the line and print it, moving to the next line
    std::getline(inf, strData);


    inf.seekg(0, std::ios::end); // move to end of file
    std::cout << inf.tellg(); // print the size of the file in bytes
}


/* Reading and writing a file at the same time using fstream

- The fstream class is capable of both reading and writing a file at the same time.
- The big caveat here is that it is not possible to switch between reading and writing arbitrarily.
- the only way to switch between the two is to perform an operation that modifies the file position (e.g. a seek).
  (If you don’t actually want to move the file pointer, you can always seek to the current position).
- If you do not do this, any number of strange and bizarre things may occur.
*/


#include <fstream>
#include <iostream>
#include <string>

int func2()
{
    std::fstream iofile{ "Sample.txt", std::ios::in | std::ios::out };

    if (!iofile)
    {
        std::cerr << "Uh oh, Sample.txt could not be opened!\n";
        return 1;
    }

    char chChar{}; // we're going to do this character by character

    while (iofile.get(chChar))
    {
        switch (chChar)
        {
            // If we find a vowel
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':

                // Back up one character
                iofile.seekg(-1, std::ios::cur);

                // let's write a # over the vowel
                iofile << '#';

                // Now we want to go back to read mode.
                iofile.seekg(iofile.tellg(), std::ios::beg);
                // Although it may seem that iofile.seekg(0, std::ios::cur) would also work, 
                // it appears some compilers may optimize this away

                break;
        }
    }

    return 0;
}

/* Other useful file functions

- To delete a file, simply use the remove() function.
*/



/* References

- https://www.learncpp.com/cpp-tutorial/random-file-io/
*/