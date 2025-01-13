/* std::cerr

- When printing information for debugging purposes, use std::cerr instead of std::cout.
- One reason for this is that std::cout may be buffered, which means a bit of time may pass between when you ask std::cout to output text and when it actually does.
- On the other hand, std::cerr is unbuffered.
*/

/* Conditionalizing your debugging code
- See example below...

- If this were a multi-file program, the #define ENABLE_DEBUG would go in a header file that’s included 
  into all code files so we can comment / uncomment the #define in a single location and have it propagate to all code files.

- Downside:
  ++ if you make a typo (e.g. misspell “DEBUG”) or forget to include the header into a code file, 
     some or all of the debugging for that file may not be enabled
*/

/* Using a logger

- C++ contains an output stream named std::clog.
- However, by default, std::clog writes to the standard error stream.

- `plog` logger
*/

#include <plog/Log.h> // Step 1: include the logger headers
#include <plog/Initializers/RollingFileInitializer.h>
#include <iostream>

#define ENABLE_DEBUG // comment out to disable debugging

int getUserInput()
{
    PLOGD << "getUserInput() called"; // PLOGD is defined by the plog library

	std::cout << "Enter a number: ";
	int x{};
	std::cin >> x;
	return x;
}

int main()
{
#ifdef ENABLE_DEBUG
std::cerr << "main() called\n";
#endif

    plog::init(plog::debug, "logs/Logfile.txt"); // Step 2: initialize the logger
    // plog::init(plog::none , "Logfile.txt"); // plog::none eliminates writing of most messages, essentially turning logging off
    
    int x{ getUserInput() };
    std::cout << "You entered: " << x << '\n';

    return 0;
}

/* References

- https://www.learncpp.com/cpp-tutorial/basic-debugging-tactics/
- https://www.learncpp.com/cpp-tutorial/more-debugging-tactics/

*/