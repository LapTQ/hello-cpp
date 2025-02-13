
/* function exits early

- Consider a function when ptr may not be deleted if the function exits early:
*/

#include <iostream>

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

void someFunction()
{
    Resource* ptr = new Resource();

    return; // the function returns early, and ptr won’t be deleted!

    delete ptr;
} // => memory leak

/* Smart pointer classes

Reminder: classes contain destructors that automatically get executed when an object of the class goes out of scope.
=> we can use a class whose sole job was to hold a pointer passed to it and deallocate that pointer when the class object went out of scope.
*/

template <typename T>
class Auto_ptr1     // Auto_ptr1 is called a "smart pointer"
{
	T* m_ptr {};
public:
	Auto_ptr1(T* ptr=nullptr)
		:m_ptr(ptr)
	{
	}

	~Auto_ptr1()
	{
		delete m_ptr;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
};

void someFunction2()
{
    Auto_ptr1<Resource> ptr { new Resource() };

    // no explicit delete here
}   // ptr destructor will be called here


/* Auto_ptr1 critical flaw with shallow copy

- we haven’t supplied a copy constructor or an assignment operator for Auto_ptr1, so C++ will provide shallow copies.
- When res2 goes out of the scope, it deletes the resource, leaving res1 with a dangling pointer.
  When res1 goes to delete the resource, it will crash.
*/

void someFunction3()
{
    Auto_ptr1<Resource> res1 { new Resource() };
    Auto_ptr1<Resource> res2 { res1 }; // res2 now points to the same Resource as res1
} // res2 destructor will be called here, leading res1 with a dangling pointer

// // You’d run into a similar problem with a function like this
void passByValue(Auto_ptr1<Resource> res)
{
}
void someFunction4()     
{
    Auto_ptr1<Resource> res { new Resource() };
    passByValue(res);
}

/*
How can we address this?
- Option 1: overload the copy constructor and assignment operator to make deep copies. But copying can be expensive.
  We also cannot return Auto_ptr1 by reference because the caller will be left with a dangling pointer.
- Option 2: Move semantics (transfer ownership of the object rather than making a copy) (mentioned in previous lesson)
*/


/* Move semantics

- Let’s update our Auto_ptr1 class to show how this can be done:
*/

template <typename T>
class Auto_ptr2
{
	T* m_ptr {};
public:
	Auto_ptr2(T* ptr=nullptr)
		:m_ptr(ptr)
	{
	}

	~Auto_ptr2()
	{
		delete m_ptr;
	}

	// A copy constructor that implements move semantics
	Auto_ptr2(Auto_ptr2& a) // note: not const
	{
		// We don't need to delete m_ptr here.  This constructor is only called when we're creating a new object, and m_ptr can't be set prior to this.
		m_ptr = a.m_ptr; // transfer our dumb pointer from the source to our local object
		a.m_ptr = nullptr; // make sure the source no longer owns the pointer
	}

	// An assignment operator that implements move semantics
	Auto_ptr2& operator=(Auto_ptr2& a) // note: not const
	{
		if (&a == this)
			return *this;

		delete m_ptr; // make sure we deallocate any pointer the destination is already holding first
		m_ptr = a.m_ptr; // then transfer our dumb pointer from the source to the local object
		a.m_ptr = nullptr; // make sure the source no longer owns the pointer
		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};

void someFunction5()
{
    Auto_ptr2<Resource> res1(new Resource());
	Auto_ptr2<Resource> res2; // Start as nullptr

	std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");   // not null
	std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");   // null

	res2 = res1; // res2 assumes ownership, res1 is set to null

	std::cout << "Ownership transferred\n";

	std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");   // null
	std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");   // not null
}


int main()
{
    // function exits early
    someFunction();

    // smart pointer classes
    someFunction2();

    // Auto_ptr1 critical flaw with shallow copy
    // someFunction3();    // will crash
    // someFunction4();    // will crash

    // Move semantics
    someFunction5();

    return 0;
}


/* std::auto_ptr, and why it was a bad idea

- std::auto_ptr, introduced in C++98 and removed in C++17, was C++’s first attempt at a standardized smart pointer.
- std::auto_ptr opted to implement move semantics just like the Auto_ptr2 class does.
- However, std::auto_ptr (and our Auto_ptr2 class) has a number of problems that makes using it dangerous.
    Read: https://www.learncpp.com/cpp-tutorial/introduction-to-smart-pointers-move-semantics/#:~:text=std%3A%3Aauto_ptr%2C%20and%20why%20it%20was%20a%20bad%20idea

- C++11 introduces: std::unique_ptr, std::weak_ptr, and std::shared_ptr. We’ll also explore the two most popular of these: 
  unique_ptr and shared_ptr in the next lesson.
*/



/* References

- https://www.learncpp.com/cpp-tutorial/introduction-to-smart-pointers-move-semantics/
*/