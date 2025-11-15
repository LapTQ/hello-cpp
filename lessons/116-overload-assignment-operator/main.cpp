

#include <algorithm>
#include <cstddef>
#include <iostream>

class Fraction
{
private:
    int m_num { 0 };
    int m_den { 1 };
public:
    Fraction(int num = 0, int den = 1)
        : m_num{ num }, m_den{ den }
    { }

    // Overload assignment operator (don't use this version in real code. See notes below)
    Fraction& operator=(const Fraction& other)
    {
        m_num = other.m_num;
        m_den = other.m_den;

        return *this;
    }

    // overload cout<< for testing
    friend std::ostream& operator<<(std::ostream& out, const Fraction& frac)
    {
        out << frac.m_num << '/' << frac.m_den;
        return out;
    }
};

void func1()
{
    Fraction a{ 1, 2 };
    Fraction b{ 3, 4 };
    std::cout << "a: " << a << '\n';
    std::cout << "b: " << b << '\n';

    a = b; // uses overloaded assignment operator
    std::cout << "a: " << a << '\n';
    std::cout << "b: " << b << '\n';
}


/* Issues due to self-assignment
*/

#include <algorithm> // for std::max and std::copy_n
#include <iostream>

class MyString
{
private:
	char* m_data {};
	int m_length {};

public:
	MyString(const char* data = nullptr, int length = 0 )
		: m_length { std::max(length, 0) }
	{
		if (length)
		{
			m_data = new char[static_cast<std::size_t>(length)];
			std::copy_n(data, length, m_data); // copy length elements of data into m_data
		}
	}
	~MyString()
	{
		delete[] m_data;
	}

	MyString(const MyString&) = default; // some compilers (gcc) warn if you have pointer members but no declared copy constructor

	// Overloaded assignment
	MyString& operator= (const MyString& str);

	friend std::ostream& operator<<(std::ostream& out, const MyString& s);
};

std::ostream& operator<<(std::ostream& out, const MyString& s)
{
	out << s.m_data;
	return out;
}

// A simplistic implementation of operator= (do not use)
MyString& MyString::operator= (const MyString& str)
{
	// if data exists in the current string, delete it
	if (m_data) delete[] m_data;        // m_data will be dangling if self-assignment occurs

	m_length = str.m_length;
	m_data = nullptr;

	// allocate a new array of the appropriate length
	if (m_length)
		m_data = new char[static_cast<std::size_t>(str.m_length)];

	std::copy_n(str.m_data, m_length, m_data);

	return *this;
}

void func2()
{
	MyString alex("Alex", 5);
	alex = alex;        // self-assignment
    std::cout << alex;  // undefined behavior
}


/* handling self-assignment with self-assignment guard

Simply add a check at the start of your assignment operator:

```
MyString& MyString::operator= (const MyString& str)
{
	if (this == &str)
		return *this;
    
    // ...
}
```
*/


/* The implicit copy assignment operator

- Unlike other operators, the compiler will provide an implicit public copy assignment operator for your class if you do not provide a user-defined one. 
- This assignment operator does memberwise assignment (essentially the same as the memberwise initialization that default copy constructors do).

- Just like other constructors and operators, you can prevent assignments by making your copy assignment operator private or using the `delete` keyword.
- if your class has const members, the compiler will instead define the implicit operator= as deleted.
*/


/* References

- https://www.learncpp.com/cpp-tutorial/overloading-the-assignment-operator/
*/