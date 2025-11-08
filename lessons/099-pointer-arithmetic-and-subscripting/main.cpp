/*

Given some pointer `ptr` that is an `int*`, and assume int is 4 bytes:
- ptr + 1 will return the address that is 4 bytes after ptr.
- ptr - 1 will return the address that is 4 bytes before ptr.
- ptr[n] is the syntax equivalent to the expression `*((ptr) + (n))`
    => this is why C-style array allow signed integer to be used as index. For example: ptr[-1].

*/

#include <iostream>

void func1()
{
    int x {};
    const int* ptr{ &x }; // assume 4 byte ints

    std::cout << ptr << ' ' << (ptr + 1) << ' ' << (ptr + 2) << '\n';
    std::cout << ptr << ' ' << (ptr - 1) << ' ' << (ptr - 2) << '\n';

    ptr++;
    std::cout << ptr << '\n';
}


/*
=> we can use pointer arithmetic to traverse an array.
*/

void printArray(const int* begin, const int* end)
{
	for (; begin != end; ++begin)   // iterate from begin up to (but excluding) end
	{
		std::cout << *begin << ' '; // dereference our loop variable to get the current element
	}

	std::cout << '\n';
}

void func2()
{
    constexpr int arr[]{ 9, 7, 5, 3, 1 };

	const int* begin{ arr };                // begin points to start element
	const int* end{ arr + std::size(arr) }; // end points to one-past-the-end element

	printArray(begin, end);
}

/* Range-based for loops over C-style arrays are implemented using pointer arithmetic
*/


int main()
{
    return 0;
}

/* References

- https://www.learncpp.com/cpp-tutorial/pointer-arithmetic-and-subscripting/
*/