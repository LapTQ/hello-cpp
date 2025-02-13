/* Shallow copy

- Because C++ does not know much about your class, the default copy constructor and default assignment operators it provides 
  use a copying method known as a memberwise copy (also known as a shallow copy):
    + using the assignment operator for overloaded operator=
    + using direct initialization for the copy constructor

- When classes are simple, this works very well.
- However, when designing classes that handle dynamically allocated memory, memberwise (shallow) copying can get us into trouble.
  It just copies the address of the pointer.
For example:
*/

#include <cstring> // for strlen()
#include <cassert> // for assert()

class MyString
{
private:
    char* m_data{}; // pointer to a dynamically allocated array of characters
    int m_length{};

public:
    MyString(const char* source = "" )
    {
        assert(source); // make sure source isn't a null string

        m_length = std::strlen(source) + 1;
        m_data = new char[m_length];

        for (int i{ 0 }; i < m_length; ++i)
            m_data[i] = source[i];
    }

    ~MyString()
    {
        delete[] m_data;
    }

    char* getString() { return m_data; }
    int getLength() { return m_length; }
};


/* Deep copying

- Doing deep copies requires that we write our own copy constructors and overloaded assignment operators.
*/

class MyString2
{
private:
    char* m_data{}; // pointer to a dynamically allocated array of characters
    int m_length{};

public:
    MyString2(const char* source = "" )
    {
        assert(source); // make sure source isn't a null string

        m_length = std::strlen(source) + 1;
        m_data = new char[m_length];

        for (int i{ 0 }; i < m_length; ++i)
            m_data[i] = source[i];
    }

    ~MyString2()
    {
        delete[] m_data;
    }

    MyString2(const MyString2& source);
    MyString2& operator=(const MyString2& source);
    void deepCopy(const MyString2& source);

    char* getString() { return m_data; }
    int getLength() { return m_length; }
};

// assumes m_data is initialized
void MyString2::deepCopy(const MyString2& source)
{
    // first we need to deallocate any value that this string is holding!
    delete[] m_data;

    m_length = source.m_length;

    // m_data is a pointer, so we need to deep copy it if it is non-null
    if (source.m_data)
    {
        m_data = new char[m_length];

        for (int i{ 0 }; i < m_length; ++i)
            m_data[i] = source.m_data[i];
    }
    else
        m_data = nullptr;
}

// Copy constructor
MyString2::MyString2(const MyString2& source)
{
    deepCopy(source);
}

// Overloaded assignment operator
MyString2& MyString2::operator=(const MyString2& source)
{
    // check for self-assignment
    if (this == &source)
        return *this;

    // do the copy
    deepCopy(source);

    return *this;
}


#include <iostream>

int main()
{
    // shallow copy
    MyString hello{ "Hello, world!" };
    {
        MyString copy{ hello }; // use default copy constructor
    } // `copy` gets destroyed here => make `hello` with a dangling pointer
    std::cout << hello.getString() << '\n'; // undefined behavior, may crash


    // deep copy
    MyString2 hello2{ "Hello, world!" };
    {
        MyString2 copy{ hello2 };
    } // `copy` gets destroyed here => `hello2` is still valid
    std::cout << hello2.getString() << '\n'; // Hello, world!

    return 0;
}


/*
- Classes in the standard library that deal with dynamic memory, such as std::string and std::vector, 
  handle all of their memory management, and have overloaded copy constructors and assignment operators that do proper deep copying. 
  So instead of doing your own memory management, you can just initialize or assign them like normal fundamental variables!
*/


/* References

- https://www.learncpp.com/cpp-tutorial/shallow-vs-deep-copying/
*/