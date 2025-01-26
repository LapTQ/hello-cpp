/* What happens if we want to use a random number generator in multiple functions or files?

Solution 1:
- create a PRNG in main() and pass it everywhere it’s needed.
=> a bit cumbersome.

Solution 2:
- create a static local std::mt19937 variable in each function that needs it
  (static so that it only gets seeded once).
=> overkill.

- What we really want is a single PRNG object that we can share and access anywhere, 
  across all of our functions and files.
*/

/* global random number generator 

- Remember how we told you to "avoid" non-const global variables? 
  This is an exception.
*/

#include "Random.h" // defines Random::mt, Random::get(), and Random::generate()
#include <cstddef> // for std::size_t
#include <iostream>

int main()
{
	std::cout << Random::get(1, 6) << '\n';   // returns int between 1 and 6
	
    
    // If we have our own distribution, we can access Random::mt directly
	std::uniform_int_distribution die6{ 1, 6 };
	for (int count{ 1 }; count <= 10; ++count)
	{
		std::cout << die6(Random::mt) << '\t';
	}

	std::cout << '\n';

	return 0;
}

/* References

- https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/
*/