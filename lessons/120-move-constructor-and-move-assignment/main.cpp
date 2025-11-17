
/* Recapping copy constructors and copy assignment
*/


#include <iostream>

template<typename T>
class Auto_ptr3
{
	T* m_ptr {};
public:
	Auto_ptr3(T* ptr = nullptr)
		: m_ptr { ptr }
	{
	}

	~Auto_ptr3()
	{
		delete m_ptr;
	}

	// Copy constructor
	Auto_ptr3(const Auto_ptr3& a)
	{
		m_ptr = new T;
		*m_ptr = *a.m_ptr;		// use assignment to copy the value
	}

	// Copy assignment
	Auto_ptr3& operator=(const Auto_ptr3& a)
	{
		// Self-assignment detection
		if (&a == this)
			return *this;

		delete m_ptr;

		m_ptr = new T;
		*m_ptr = *a.m_ptr;

		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};

class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};

Auto_ptr3<Resource> generateResource()
{
	Auto_ptr3<Resource> res{new Resource};
	return res; // this return value will invoke the copy constructor
}

void func1()
{
	Auto_ptr3<Resource> mainres;
	mainres = generateResource(); // this assignment will invoke the copy assignment
}

/*
- func1 prints:
```
Resource acquired
Resource acquired
Resource destroyed
Resource acquired
Resource destroyed
Resource destroyed
```
Here is what happens:
- res is constructed in generateResource() => Resource acquired
- When res is returned by value, it's copy constructed to a temporary object => Resource acquired
- Res is destroyed => Resource destroyed
- The temporary object is copy assigned to mainres => Resource acquired
- The temporary object is destroyed => Resource destroyed
- mainres is destroyed => Resource destroyed 

=> not efficient. However, with move semantics, we can do better.
*/


/* Move constructors and move assignment

- whereas the copy flavors of these functions take a const l-value reference parameter,
	the move flavors of these functions use non-const rvalue reference parameters.
*/


template<typename T>
class Auto_ptr4
{
	T* m_ptr {};
public:
	Auto_ptr4(T* ptr = nullptr)
		: m_ptr { ptr }
	{
	}

	~Auto_ptr4()
	{
		delete m_ptr;
	}

	// Copy constructor
	Auto_ptr4(const Auto_ptr4& a)
	{
		m_ptr = new T;
		*m_ptr = *a.m_ptr;
	}

	// Copy assignment
	Auto_ptr4& operator=(const Auto_ptr4& a)
	{
		// Self-assignment detection
		if (&a == this)
			return *this;

		delete m_ptr;

		m_ptr = new T;
		*m_ptr = *a.m_ptr;

		return *this;
	}

	// Move constructor
	Auto_ptr4(Auto_ptr4&& a) noexcept
		: m_ptr(a.m_ptr)
	{
		a.m_ptr = nullptr;	// don't forget
	}

	// Move assignment
	Auto_ptr4& operator=(Auto_ptr4&& a) noexcept
	{
		// Self-assignment detection
		if (&a == this)
			return *this;

		// Release any resource we're holding
		delete m_ptr;

		// Transfer ownership of a.m_ptr to m_ptr
		m_ptr = a.m_ptr;
		a.m_ptr = nullptr;	// don't forget

		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};

Auto_ptr4<Resource> generateResource2()
{
	Auto_ptr4<Resource> res{new Resource};
	return res; // moved instead of copied, even though res is an l-value!!! Explain below.
}

void func2()
{
	Auto_ptr4<Resource> mainres;
	mainres = generateResource2(); // this assignment will invoke the move assignment
}

/*
- func2 prints:
```
Resource acquired
Resource destroyed
```

Here is what happens:
- res is constructed in generateResource2() => Resource acquired
- When res is returned by value, it's move constructed to a temporary object, then res is destroyed.
- The temporary object is move assigned to mainres, then the temporary object is destroyed.
- mainres is destroyed => Resource destroyed
*/


/* When is move constructor/assignment is called instead of copy constructor/assignment?

- They are called when they are defined and the argument is an rvalue.
- The copy constructor/assignment is called otherwise.
*/


/* Implicit move constructor and move assignment operator

The compiler will create an implicit move constructor and move assignment operator if all of the following are true:
+ There are no user-declared copy constructors or copy assignment operators.
+ There are no user-declared move constructors or move assignment operators.
+ There is no user-declared destructor.

These move functions will do a member-wise move as follows:
+ If member has a move constructor or move assignment (as appropriate), it will be invoked.
+ Otherwise, the member will be copied.

Warning: This means that implicit constructor/assignment will copy pointers, not move them! If you want to move a pointer member, you will need to define the move constructor and move assignment yourself.
*/


/* Automatic l-values returned by value may be moved instead of copied

- In the generateResource2(), when res is returned by value, it is an l-value. But it is moved instead of copied.
- The C++ specification has a special rule: automatic objects returned from a function by value can be moved even if they are l-values.
*/


/* Disabling copying

- we can make our Auto_ptr4 better by disabling copying.
```
Auto_ptr5(const Auto_ptr5& a) = delete;
Auto_ptr5& operator=(const Auto_ptr5& a) = delete;
```

This is good because, we should probably passing Auto_ptr5 to a function by const l-value reference instead of by value.
This makes Auto_ptr5 smarter, and in fact the standard library contains a class very much like this one. 
*/


/* std::move

- in the mySwapCopy, we're making expensive but not necessary copies. a and b are l-values, so the copy constructor and copy assignment are called.

- std::move is a function that casts (using static_cast) its argument into an r-value reference, so that move semantics can be invoked
*/

template <typename T>
void mySwapCopy(T& a, T& b)
{
	T tmp { a }; // invokes copy constructor because a is an l-value
	a = b; // invokes copy assignment because b is an l-value
	b = tmp; // invokes copy assignment because tmp is an l-value
}

#include <utility> // for std::move

template <typename T>
void mySwapMove(T& a, T& b)
{
	T tmp { std::move(a) }; // invokes move constructor
	a = std::move(b); // invokes move assignment
	b = std::move(tmp); // invokes move assignment
}

void func3()
{
	Auto_ptr4<Resource> res1{new Resource};
	Auto_ptr4<Resource> res2{new Resource};

	mySwapCopy(res1, res2); // expensive copies
	mySwapMove(res1, res2); // efficient moves
}

#include <vector>
#include <string>

void func4()
{
	std::vector<std::string> v;

	// We use std::string because it is movable (std::string_view is not)
	std::string str { "Knock" };

	std::cout << "Copying str\n";
	v.push_back(str); // calls l-value version of push_back => copies
	std::cout << "str: " << str << '\n';	// str is unchanged
	std::cout << "vector: " << v[0] << '\n';

	std::cout << "\nMoving str\n";
	v.push_back(std::move(str)); // calls r-value version of push_back => moves
	std::cout << "str: " << str << '\n'; // str is now indeterminate
	std::cout << "vector:" << v[0] << ' ' << v[1] << '\n';
}

/* 
- When we move the value from a temporary object, it doesn’t matter what value the moved-from object is left with, 
  because the temporary object will be destroyed immediately anyway.
- Because we can continue to access these objects after their values have been moved, it is useful to know what value they are left with.
- There are two schools of thought here:
	+ One school believes that objects that have been moved from should be reset back to some default / zero state (like str in the example above).
	+ other school believes that we should do whatever is most convenient

	the C++ standard says, “Unless otherwise specified, moved-from objects shall be placed in a valid but unspecified state.”
	=> str can be any valid string, including an empty string, the original string => we should avoid using the value of a moved-from object, 
	as the results will be implementation-specific.

- With a moved-from object, it is safe to call any function that does not depend on the current value of the object.
*/


int main()
{
	// Recap copy constructor and copy assignment
	func1();


	// Move constructor and move assignment
	func2();


	// std::move
	func3();
	func4();


	return 0;
}


/* Where else is std::move useful?

- std::move can also be useful when sorting an array of elements. Many sorting algorithms work by swapping pairs of elements.
- It can also be useful if we want to move the contents managed by one smart pointer to another.
*/



/* References

- https://www.learncpp.com/cpp-tutorial/move-constructors-and-move-assignment/
- https://www.learncpp.com/cpp-tutorial/stdmove/
*/