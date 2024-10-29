#include<iostream>

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

   If no characters could be extracted in this step, e.g. typing a non-digit for a
   int y, the object being extracted to is assigned the value 0 (as of C++11), 
   and any future extractions will immediately fail (until until the 
   input stream is cleared).

Any non-extracted characters (including newlines) remain available for the next extraction attempt.

*/