/*
There are three different ways to overload operators: 
- the friend function way
- the normal function way.
- the member function way
*/


/* Using friend functions 
*/

#include <iostream>

class Cents
{
private:
	int m_cents {};

public:
	Cents(int cents) : m_cents{ cents } { }

	friend Cents operator+(const Cents& c1, const Cents& c2);
	friend Cents operator+(const Cents& c1, int value);
	friend Cents operator+(int value, const Cents& c1);

	int getCents() const { return m_cents; }
};

// note: this function is not a member function!
Cents operator+(const Cents& c1, const Cents& c2)
{
	return c1.m_cents + c2.m_cents;
}

// // note: this function is not a member function!
Cents operator+(const Cents& c1, int value)
{
    return c1.m_cents + value;
}

// note: this function is not a member function!
Cents operator+(int value, const Cents& c1)
{
    return value + c1.m_cents;
}


/* Using normal functions 

- Prefer overloading operators as normal functions instead of friends.
*/

// note: this function is not a member function nor a friend function!
Cents operator-(const Cents& c1, const Cents& c2)
{
	return { c1.getCents() - c2.getCents() };
}


/* Using member function
*/

class Cents3
{
private:
	int m_cents {};

public:
	Cents3(int cents) : m_cents{ cents } { }

	Cents3 operator+(int value) const;

	int getCents() const { return m_cents; }
};

// note: this function is a member function!
Cents3 Cents3::operator+(int value) const
{
	return Cents3{ m_cents + value };
}


int main()
{
	Cents cents1{ 6 };
	Cents cents2{ 8 };

	// Using friend functions
	Cents centsSum{ cents1 + cents2 }; // 14
    Cents centsSum2{ cents1 + 8 }; // 14
    Cents centsSum3{ 6 + cents2 }; // 14
    std::cout << "I have " << centsSum.getCents() << " cents.\n";
    std::cout << "I have " << centsSum2.getCents() << " cents.\n";
    std::cout << "I have " << centsSum3.getCents() << " cents.\n";

	// Using normal functions
	Cents centsSub{ cents1 - cents2 }; // -2
	std::cout << "I have " << centsSub.getCents() << " cents.\n";


	// Using member functions
	Cents3 cents3{ 6 };
	Cents3 cents4{ cents3 + 8 }; // 14
	std::cout << "I have " << cents4.getCents() << " cents.\n";

	return 0;
}

/* 
- When dealing with binary operators that don’t modify the left operand (e.g. operator+), the normal or friend function version is typically preferred.
- When dealing with binary operators that do modify the left operand (e.g. operator+=), the member function version is typically preferred.
- Unary operators are usually overloaded as member functions as well, since the member version has no parameters.
*/


/* References

- https://www.learncpp.com/cpp-tutorial/overloading-the-arithmetic-operators-using-friend-functions/
- https://www.learncpp.com/cpp-tutorial/overloading-operators-using-normal-functions/
*/