
/* std::shared_ptr

Unlike std::unique_ptr, which is designed to singly own and manage a resource, 
std::shared_ptr is meant to solve the case where you need multiple smart pointers co-owning a resource.

- Internally, std::shared_ptr keeps track of how many std::shared_ptr are sharing the resource.
- As long as at least one std::shared_ptr is pointing to the resource, the resource will not be deallocated, 
  even if individual std::shared_ptr are destroyed.
- As soon as the last std::shared_ptr managing the resource goes out of scope (or is reassigned to point at something else), 
  the resource will be deallocated.

- It's important not to create a second shared pointer from the resource directly.
*/

#include <iostream>
#include <memory> // for std::shared_ptr

class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};

void func1Correct()
{
	Resource* res { new Resource };
	std::shared_ptr<Resource> ptr1{ res };
	{
		std::shared_ptr<Resource> ptr2 { ptr1 }; // make another std::shared_ptr from ptr1

		std::cout << "Killing one shared pointer\n";
	} // ptr2 goes out of scope here, but nothing happens

	std::cout << "Killing another shared pointer\n";
} // ptr1 goes out of scope here, and the allocated Resource is destroyed

void func1Wrong()
{
	Resource* res { new Resource };
	std::shared_ptr<Resource> ptr1{ res };
	{
		std::shared_ptr<Resource> ptr2 { res }; // make another std::shared_ptr from res

		std::cout << "Killing one shared pointer\n";
	} // ptr2 goes out of scope here, and the allocated Resource is destroyed

	std::cout << "Killing another shared pointer\n";
} // ptr1 goes out of scope here, and the allocated Resource is destroyed 


/* std::make_shared

- Much like std::make_unique() can be used to create a std::unique_ptr in C++14, std::make_shared() can (and should) be used to make a std::shared_ptr.
*/

void func2()
{
	auto ptr1 { std::make_shared<Resource>() };
	{
		auto ptr2 { ptr1 }; // create ptr2 using copy of ptr1

		std::cout << "Killing one shared pointer\n";
	}

	std::cout << "Killing another shared pointer\n";

}


/* Circular dependency issues with std::shared_ptr

- At the end of func3, no deallocations took place: to deallocate Ricky, we need to deallocate Ricky’s partner which is Lucy, 
  and to deallocate Lucy, we need to deallocate Lucy’s partner which is Ricky.
- similarly, at the end of func4, no deallocations took place.
*/

class Person
{
	std::string m_name;
	std::shared_ptr<Person> m_partner;

public:

	Person(const std::string &name): m_name(name)
	{
		std::cout << m_name << " created\n";
	}
	~Person()
	{
		std::cout << m_name << " destroyed\n";
	}

	friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2)
	{
		if (!p1 || !p2)
			return false;

		p1->m_partner = p2;
		p2->m_partner = p1;

		std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

		return true;
	}
};

void func3()
{
	auto lucy { std::make_shared<Person>("Lucy") }; // create a Person named "Lucy"
	auto ricky { std::make_shared<Person>("Ricky") }; // create a Person named "Ricky"

	partnerUp(lucy, ricky);
}
// Lucy created
// Ricky created
// Lucy is now partnered with Ricky

class Resource2
{
public:
	std::shared_ptr<Resource2> m_ptr {}; // initially created empty

	Resource2() { std::cout << "Resource acquired\n"; }
	~Resource2() { std::cout << "Resource destroyed\n"; }
};

void func4()
{ 
	auto ptr1 { std::make_shared<Resource2>() };

	ptr1->m_ptr = ptr1;
}
// Resource acquired


/* std::weak_ptr was designed to solve the “cyclical ownership” problem

- A std::weak_ptr is an observer -- it can observe and access the same object as a std::shared_ptr (or other std::weak_ptrs) 
  but it is not considered an owner => std::weak_ptr does not count in the number of owners when a std::shared pointer goes out of scope

- One downside of std::weak_ptr is that std::weak_ptr are not directly usable (they have no operator->).
- To use a std::weak_ptr, you must first convert it into a std::shared_ptr using the lock() member function.

Avoiding dangling pointers with std::weak_ptr:
- Because std::weak_ptr won’t keep an owned resource alive, it’s similarly possible for 
  a std::weak_ptr to be left pointing to a resource that has been deallocated by a std::shared_ptr.
- The easiest way to test whether a std::weak_ptr is valid is to use the expired() member function, 
  which returns true if the std::weak_ptr is pointing to an invalid object, and false otherwise.
*/

class Person2
{
	std::string m_name;
	std::weak_ptr<Person2> m_partner; // note: This is now a std::weak_ptr

public:

	Person2(const std::string &name): m_name(name)
	{
		std::cout << m_name << " created\n";
	}
	~Person2()
	{
		std::cout << m_name << " destroyed\n";
	}

	friend bool partnerUp(std::shared_ptr<Person2> &p1, std::shared_ptr<Person2> &p2)
	{
		if (!p1 || !p2)
			return false;

		p1->m_partner = p2;
		p2->m_partner = p1;

		std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

		return true;
	}

	std::shared_ptr<Person2> getPartner() const
	{
		if (m_partner.expired()) // check if the weak_ptr is expired
			return nullptr;

		return m_partner.lock();
	}

	const std::string& getName() const { return m_name; }
};

void func5()
{
	auto lucy { std::make_shared<Person2>("Lucy") };
	auto ricky { std::make_shared<Person2>("Ricky") };

	partnerUp(lucy, ricky);

	auto partner = ricky->getPartner(); // get shared_ptr to Ricky's partner
	std::cout << ricky->getName() << "'s partner is: " << partner->getName() << '\n';
}
// Lucy created
// Ricky created
// Lucy is now partnered with Ricky
// Ricky's partner is: Lucy
// Ricky destroyed
// Lucy destroyed


int main()
{   
    // std::shared_ptr
    func1Correct();
    func1Wrong();


    // Circular dependency issues with std::shared_ptr
    func3();
	func4();


	// std::weak_ptr was designed to solve the “cyclical ownership” problem
	func5();

    return 0;
}


/* Convert between Shared pointers and Unique pointers

- A std::unique_ptr can be converted into a std::shared_ptr via a special std::shared_ptr constructor that accepts a std::unique_ptr r-value. 
  The contents of the std::unique_ptr will be moved to the std::shared_ptr.

- However, std::shared_ptr can not be safely converted to a std::unique_ptr.
*/


/* std::shared_ptr and arrays

- In C++17 and earlier, std::shared_ptr does not have proper support for managing arrays.
*/


/* References

- https://www.learncpp.com/cpp-tutorial/stdshared_ptr/
*/