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

	return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/overloading-the-arithmetic-operators-using-friend-functions/
- https://www.learncpp.com/cpp-tutorial/overloading-operators-using-normal-functions/
*/