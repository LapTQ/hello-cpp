/* Command line arguments
- argc: count of the number of arguments passed to the program, always be at least 1.
- argv: C-style array of char pointers (the length of this array is argc), each of which points to a C-style string.
*/


/* Dealing with numeric arguments

- To use a command line argument as a number, you must convert it from a string to a number.

- std::stringstream works much like std::cin
*/

#include <iostream>
#include <sstream> // for std::stringstream
#include <string>

int main(int argc, char* argv[])
{
    // Command line arguments
    std::cout << "There are " << argc << " arguments:\n";
    for (int count{ 0 }; count < argc; ++count)
        std::cout << count << " " << argv[count] << '\n';


    // Dealing with numeric arguments
    if (argc <= 1)
	{
		// On some operating systems, argv[0] can end up as an empty string instead of the program's name.
		// We'll conditionalize our response on whether argv[0] is empty or not.
		if (argv[0])
			std::cout << "Missing argument. Usage: " << argv[0] << " <number>" << '\n';
		else
			std::cout << "Missing argument. Usage: <program name> <number>" << '\n';

		return 1;
	}

	std::stringstream convert{}; // set up a stringstream variable named convert, initialized with the input from argv[1]

	std::string mystr{};
    convert << argv[1]; // add argv[1] to the stringstream
	if (!(convert >> mystr)) // do the conversion
		mystr = ""; // if conversion fails
    
    int myint{};
    convert.clear(); // clear any errors
    convert.str(""); // clear the contents of the stringstream
    convert << argv[2];
    if (!(convert >> myint))
        myint = 0;

    std::cout << "Got string: " << mystr << '\n';
	std::cout << "Got integer: " << myint << '\n';

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/command-line-arguments/
*/