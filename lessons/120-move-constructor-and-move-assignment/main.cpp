
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
		*m_ptr = *a.m_ptr;
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
	return res; // moved instead of copied, even though res is an l-value!!!
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


/* Why is move constructor/assignment is called instead of copy constructor/assignment?

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

Warning: this means that pointers will be copied, not moved!
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


int main()
{
	// Recap copy constructor and copy assignment
	func1();


	// Move constructor and move assignment
	func2();


	return 0;
}



/* References

- https://www.learncpp.com/cpp-tutorial/move-constructors-and-move-assignment/
*/