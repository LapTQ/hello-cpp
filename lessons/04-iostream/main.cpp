#include<iostream>
#include <limits> // for std::numeric_limits

int main()
{
    std::cout << "Hello" << " world!";

    // a newline
    std::cout << std::endl;
    // or
    std::cout << "\n";
    /*
    Using std::endl is often inefficient, as it actually does two jobs: it outputs 
    a newline (moving the cursor to the next line of the console), and it flushes 
    the buffer (which is slow). If we output multiple lines of text ending with 
    std::endl, we will get multiple flushes, which is slow and probably unnecessary.
    */

    int x {}; // value-initialization
    std::cout << "x = ";
    std::cin >> x;
    
    // input more than one value on a single line. Values entered should be separated by whitespace (spaces, tabs, or newlines)
    int y {};
    std::cout << "x, y = ";
    std::cin >> x >> y;

    // 2 tests
    std::cout << "You're going to input x and y." << "\n" << "Test 1: type 4, press Enter, then type 5." << "\n" << "x = ";
    std::cin >> x;
    std::cout << "y = ";
    std::cin >> y;
    std::cout << "----> " << x << ", " << y << "\n";

    std::cout << "Test 2: type 4, space, 5, press Enter." << "\n" << "x = ";
    std::cin >> x;
    std::cout << "y = ";
    std::cin >> y;
    std::cout << "----> " << x << ", " << y << "\n";
    std::cout << "When std::cin >> y is encountered, the program will not wait for input. Instead, the 5 that is still in the input buffer is extracted to variable y.";


    // [code snippet] clear the input buffer
    std::cin.ignore(100, '\n');  // clear up to 100 characters out of the buffer, or until a '\n'
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore all characters up to the next ‘\n’

    
    // check if there is extraneous input
    std::cout << (!std::cin.eof() && std::cin.peek() != '\n') << "\n";

    
    // [code snippet] handle failed extractions or overflow of a numeric type
    if (std::cin.fail()) // equivalent to if (!std::cin)
    {
        if (std::cin.eof()) // If the user entered an EOF
        {
            std::exit(0); // Shut down the program now
        }

        std::cin.clear(); // Put us back in 'normal' operation mode
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');     // And remove the bad input
    }

    return 0;
}

/* how is output sent to std::cout in C++?

Statements in our program request that output be sent to the console. 
However, that output is typically not sent to the console immediately. 
Instead, the requested output “gets in line”, and is stored in a region 
of memory set aside to collect such requests (called a buffer). 
Periodically, the buffer is flushed, meaning all of the data collected 
in the buffer is transferred to its destination (in this case, the console).

The opposite of buffered output is unbuffered output. With unbuffered output, 
each individual output request is sent directly to the output device.
Writing data to a buffer is typically fast, whereas transferring a batch 
of data to an output device is comparatively slow. Buffering can significantly 
increase performance by batching multiple output requests together to 
minimize the number of times output has to be sent to the output device.

*/

/* '\n' (single characters) or "\n" (text)?

* For non-output cases, we prefer '\n'.
* For standard output statements, we prefer "\n":
    * It’s simpler to double-quote all outputted text rather than having to 
      determine what should be single-quoted and double-quoted.
    * More importantly, it helps avoid inadvertent multicharacter literals (discuss later).
*/

/* std::cin is buffered

Similar to outputting data, inputting data is also a two stage process:
* The individual characters you enter as input are added to the end of an 
  input buffer (inside std::cin). The enter key is also stored as a '\n' character.
* The extraction operator ‘>>’ removes characters from the front of the 
  input buffer and converts them into a value that is assigned to the 
  associated variable.

*/

/* How >> works (simplified)

1. First, leading whitespace is discared from the input buffer.
2. If the input buffer is now empty, >> will wait for the user input. 
   Leading whitespace is again discarded.
3. >> then extracts as many consecutive characters as it can, until it 
   encounters either a newline character or a character that is not valid
   for the variable being extracted to.

   If no characters could be extracted in this step, e.g. typing a non-digit `a` character 
   for an int y, 3 things happen at this point:
   + the object being extracted to is assigned the value 0 (as of C++11)
   + `a` is left in the input buffer
   + std::cin goes into “failure mode” (until the clear() function is called): any requests for further extraction are ignored.
     This means that instead waiting for us to enter an operation, the input prompt is silently skipped.

Any non-extracted characters (including newlines) remain available for the next extraction attempt.

*/

/*
- The std::cin.eof() function returns true if the last input operation 
  reached the end of the input stream.
- The std::cin.peek() function allows us to peek at the next character 
  in the input stream without extracting it.


- In C++, EOF is an error state, not a character. 
  Different OSes have special character combinations that are treated as a “user-entered EOF request”. 
  These are sometimes called “EOF characters”.
*/


/* References

- https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/
*/