/*
- When an object goes out of scope normally, or a dynamically allocated object is 
  explicitly deleted using the delete keyword, the class destructor is automatically called.

- For simple classes, a destructor is not needed because C++ will automatically clean up the memory for you.
- However, if your class object is holding any resources (e.g. dynamic memory, or a file or database handle),
  the destructor is a good place to clean up those resources.
*/


#include <iostream>
#include <cassert>
#include <cstddef>

class IntArray
{
private:
	int* m_array{};

public:
	IntArray(int length) // constructor
	{
		assert(length > 0);

		m_array = new int[static_cast<std::size_t>(length)]{};
	}

	~IntArray() // destructor
	{
		// Dynamically delete the array we allocated earlier
		delete[] m_array;
	}
};

int main()
{
	IntArray ar ( 10 ); // allocate 10 integers
	
	return 0;
} // ar is destroyed here, so the ~IntArray() destructor function is called here


/* References

- https://www.learncpp.com/cpp-tutorial/destructors/
*/