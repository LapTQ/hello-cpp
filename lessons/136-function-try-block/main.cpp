/*
- Try and catch blocks work well enough in most cases, but there is one particular case in which 
  they are not sufficient. Consider the following example:
*/

#include <iostream>

class A
{
private:
	int m_x;
public:
	A(int x) : m_x{x}
	{
		if (x <= 0)
			throw 1; // Exception thrown here
	}
};

class B1 : public A
{
public:
	B1(int x) : A{x} // A initialized in member initializer list of B
	{
		// What happens if creation of A fails and we want to handle it here?
	}
};


/* Function try blocks

- ... designed to allow you to establish an exception handler around the 
body of an entire function, rather than around a block of code.

- A function-level catch block for a constructor must either throw a new exception 
  or rethrow the existing exception -- they are not allowed to resolve exceptions!
  Reaching the end of the catch block will implicitly rethrow.
*/

class B2 : public A
{
public:
	B2(int x) try : A{x} // note addition of try keyword here
	{
	}
	catch (...)
	{
        std::cerr << "Exception caught\n";

        throw; // rethrow the existing exception
	}
};



/* References

- https://www.learncpp.com/cpp-tutorial/function-try-blocks/
*/