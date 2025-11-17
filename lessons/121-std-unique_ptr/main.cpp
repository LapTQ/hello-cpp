/*
- C++11 standard library ships with 4 smart pointer classes: std::auto_ptr (removed in C++17), std::unique_ptr, 
  std::shared_ptr, and std::weak_ptr. std::unique_ptr is by far the most used smart pointer class.
*/


/* std::unique_ptr

- ... should be used to manage any dynamically allocated object that the ownership is not shared by multiple objects.
- std::unique_ptr is designed with move semantics in mind, copy initialization and copy assignment are disabled.

- std::unique_ptr has an overloaded operator* and operator->. 
  Operator* returns a reference to the managed resource, and operator-> returns a pointer.
- before we use either of these operators, we should check whether the std::unique_ptr actually has a resource.
  Because, it might be created empty, or the resource it was managing might have been moved elsewhere.
*/

#include <iostream>
#include <memory> // for std::unique_ptr

class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};

std::ostream& operator<<(std::ostream& out, const Resource&)
{
	out << "I am a resource";
	return out;
}

void func0()
{
	std::unique_ptr<Resource> res1{ new Resource{} }; // Resource created here
	std::unique_ptr<Resource> res2{}; // Start as nullptr

	std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
	std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");

	// res2 = res1; // Won't compile: copy assignment is disabled
	res2 = std::move(res1); // res2 assumes ownership, res1 is set to null

	std::cout << "Ownership transferred\n";

	std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
	std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");
}

void func1()
{
	// allocate a Resource object and have it owned by std::unique_ptr
	std::unique_ptr<Resource> res{ new Resource() };

    if (res)    // make sure res contains a Resource
    {
        std::cout << *res << '\n';  // dereference operator*
    }
}


/* std::unique_ptr and arrays

- std::unique_ptr is smart enough to know whether to use scalar delete or array delete.
- It is okay to use std::unique_ptr with both scalar objects and arrays.
- However, std::array or std::vector (or std::string) are almost always better choices than using std::unique_ptr with a fixed array, dynamic array, or C-style string.
*/


/* std::make_unique

- C++14 comes with an additional function named std::make_unique().
- Use of std::make_unique() is optional, but it recommended over creating a std::unique_ptr yourself.
  It makes the code simpler, and in C++14 it resolves an exception safety issue.
*/

class Fraction
{
private:
	int m_numerator{ 0 };
	int m_denominator{ 1 };

public:
	Fraction(int numerator = 0, int denominator = 1) :
		m_numerator{ numerator }, m_denominator{ denominator }
	{
	}

	friend std::ostream& operator<<(std::ostream& out, const Fraction &f1)
	{
		out << f1.m_numerator << '/' << f1.m_denominator;
		return out;
	}
};


int func2()
{
	// Create a single dynamically allocated Fraction with numerator 3 and denominator 5
	auto f1{ std::make_unique<Fraction>(3, 5) };
	std::cout << *f1 << '\n';

	// Create a dynamically allocated array of Fractions of length 4
	auto f2{ std::make_unique<Fraction[]>(4) };
	std::cout << f2[0] << '\n';

	return 0;
}


/* Returning/passing std::unique_ptr from/to a function

- std::unique_ptr can be safely returned from a function by value.
    - in C++14 or earlier, move semantics will be called
    - in C++17 or later, the return will be elided.
- In general, you should not return std::unique_ptr by pointer (ever) or reference (unless you have a specific compelling reason to).

- If you want the function to take ownership of the contents of the pointer, pass the std::unique_ptr by value. 
  Note that because copy semantics have been disabled, you’ll need to use std::move to actually pass the variable in.

- Although you can pass the std::unique_ptr by const reference, it’s better to just pass the resource (by pointer or reference)
  To get a raw pointer from a std::unique_ptr, you can use the get() member function.
  
*/
#include <string>

std::unique_ptr<std::string> createString()
{
    return std::make_unique<std::string>("Knock");	// okay, return std::unique_ptr by value
}

void takeOwnership(std::unique_ptr<std::string> res) // pass by value to take ownership
{
	if (res)
	;
} // res is destroyed here

void useResource(const std::string* res)	// okay, just pass the resource
{
	if (res)
	;
}

int func3()
{
    auto ptr{ createString() };

	auto res{ std::make_unique<std::string>("Knock") };
	takeOwnership(std::move(res));
	std::cout << *res << '\n'; // this will crash

	auto res2{ std::make_unique<std::string>("Knock") };
	useResource(res2.get());
	std::cout << *res2 << '\n'; // this is okay

	return 0;

}


int main()
{
    // std::unique_ptr
    func1();


    // std::make_unique
    func2();


	// Returning/passing std::unique_ptr from/to a function
	func3();

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/stdunique_ptr/
*/