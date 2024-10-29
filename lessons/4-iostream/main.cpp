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
    std::cin >> x;
    
    // input more than one value on a single line. Values entered should be separated by whitespace (spaces, tabs, or newlines)
    int y {};
    std::cin >> x >> y;

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
    * It’s simpler to double-quote all outputted text rather than having to determine what should be single-quoted and double-quoted.
    * More importantly, it helps avoid inadvertent multicharacter literals (discuss later).
*/

/* std::cin is buffered

Similar to outputting data, inputting data is also a two stage process:

*/