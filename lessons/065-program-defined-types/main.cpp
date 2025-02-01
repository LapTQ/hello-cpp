/*
- C++ has two different categories of compound types to create program-defined types:
    + enumerated types
    + class types
*/

/* Using program-defined types throughout a multi-file program

- program-defined types are typically defined in header files.
- These header files are typically given the same name as the program-defined type
  E.g., type named Fraction would be defined in Fraction.h

- To allow for this without violating ODR, types are partially exempt 
  from the one-definition rule: a given type is allowed to be defined in multiple code files.
*/

#include "Fraction.h"

int main()
{
	Fraction f { 3, 4 };

	return 0;
}

/* References

- https://www.learncpp.com/cpp-tutorial/introduction-to-program-defined-user-defined-types/
*/