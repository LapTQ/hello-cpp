/*
C++ supports three basic types of memory allocation:
- Static memory allocation: happens for static and global variables.
  Memory for these types of variables is allocated once when your program is run and persists throughout the life of your program.
- Automatic memory allocation: happens for function parameters and local variables. 
  Memory for these types of variables is allocated when the relevant block is entered, 
  and freed when the block is exited.
- Dynamic memory allocation

Both static and automatic allocation have two things in common:
- The size of the variable / array must be known at compile time.
- Memory allocation and deallocation happens automatically.
=> Limitation:
    - For example, we may want to read in a number of records from disk, but we don’t know in advance how many records there are.
      the best we can do is try to make a guess the maximum size.
      => wasted memory if the variables aren’t actually used.
    - most normal variables (including fixed arrays) are allocated in stack memory, which is generally quite small.

Dynamic memory allocation: 
- is a way for running programs to request memory from the operating system when needed.
  This memory comes from heap memory.
- Unlike static or automatic memory, the program itself is responsible for disposing of dynamically allocated memory.

- Note that accessing heap-allocated objects is generally slower than accessing stack-allocated objects.
*/


/* Dynamically allocating "single" variables

- Don't forget to deallocate memory when you're done with it.
    + The OS is then free to reassign that memory to another application. 
    + We don't actually delete the `ptr` variable, 
    it can be assigned a new value (e.g., nullptr) just like any other variable.
*/


/* Deallocating memory may create multiple dangling pointers
*/


/* Operator new can fail

- When requesting memory from the OS, in rare circumstances, the OS may not have any memory to grant.

- By default, if new fails, a bad_alloc exception is thrown. 
    If this exception isn’t properly handled, the program will simply crash.
- Alternatively, we can use return a null pointer by adding the constant std::nothrow:
*/


/* Memory leaks

- ... when your program loses the address of some bit of dynamically allocated memory 
  before giving it back to the OS.

- The OS cannot use this memory, because the memory is considered to be still in use by your program.
*/

void exampleMemoryLeak()
{
    int* ptr{ new int{} };

    // forget to `delete ptr;` here
} // ptr goes out of scope, we lost the address of the memory we allocated


void exampleMemoryLeak2()
{
    int value = 5;
    int* ptr{ new int{} }; // allocate memory
    // forget to `delete ptr;` here
    ptr = &value; // old address lost, memory leak results
}


/* Dynamically allocating arrays

- ... allows us to choose an array length at runtime.

- In these lessons, we’ll be dynamically allocating C-style arrays.
*/


/* Initializing dynamically allocated arrays
*/


/* Resizing arrays

- C++ does not provide a built-in way to resize an array that has already been allocated.

Solutions:
- Allocate a new array, copy the elements, and delete the old array.
  => Error prone, especially when the elements type is a class.
- Use a `std::vector` instead.
*/


/* Destructor

- When an object goes out of scope normally, or a dynamically allocated object is 
  explicitly deleted using the delete keyword, the class destructor is automatically called.

- For simple classes, a destructor is not needed because C++ will automatically clean up the memory for you.
- However, if your class object is holding any resources (e.g. dynamic memory, or a file or database handle),
  the destructor is a good place to clean up those resources.
*/


#include <cstddef>
#include <cassert>
#include <iostream>

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
    // Dynamically allocating "single" variables
    int* ptr{ new int }; 
    int* ptr1{ new int (5) }; // use direct initialization
    int* ptr2{ new int { 6 } }; // use uniform initialization

    delete ptr;     // return the memory to the OS
    ptr = nullptr;
    delete ptr1;
    ptr1 = nullptr;
    delete ptr2;
    ptr2 = nullptr;


    // Deallocating memory may create multiple dangling pointers
    int* ptr3{ new int{} };
    int* otherPtr{ ptr3 }; // otherPtr is now pointed at that same memory location
    delete ptr3; // ptr3 and otherPtr are now dangling pointers.
    ptr3 = nullptr;
    // however, otherPtr is still a dangling pointer!
    

    // Operator new can fail
    int* value { new (std::nothrow) int };


    // Dynamically allocating arrays
    std::size_t length{ 10 };   // not constepxr
    int* array{ new int[length]{} }; 
    array[0] = 5;
    delete[] array;


    // Initializing dynamically allocated arrays
    int* array2{ new int[5]{ 9, 7, 5, 3, 1 } };
    auto* array3{ new int[5]{ 9, 7, 5, 3, 1 } };    // type deduction
    int* array4{ new int[]{ 9, 7, 5, 3, 1 } }; // Explicitly stating the size of the array is optional.
    delete[] array2;
    delete[] array3;
    delete[] array4;


    // Destructor
    IntArray ar ( 10 ); // allocate 10 integers

    return 0;
} // ar is destroyed here, so the ~IntArray() destructor function is called here


/* References

- https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/
- https://www.learncpp.com/cpp-tutorial/dynamically-allocating-arrays/
- https://www.learncpp.com/cpp-tutorial/destructors/
*/