/* Copy constructor

- A copy constructor is a constructor that is used to initialize an object with an existing object of the same type
*/

/* implicit copy constructor

- If you do not provide a copy constructor for your classes, C++ will create a public implicit copy constructor.
- By default, the implicit copy constructor will do memberwise initialization.
*/


#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

void func1()
{
    Fraction f { 5, 3 };
    Fraction fCopy { f }; // What constructor is used here? => implicit copy constructor
}


/* Defining your own copy constructor

- A copy constructor should NOT do anything other than copy an object.
  This is because the compiler may optimize the copy constructor out in certain cases
  => your extra code may not be executed.
- The copy constructor’s parameter must be a reference.

=> Prefer the implicit copy constructor.
*/

class Fraction2
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    Fraction2(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    // Copy constructor
    Fraction2(const Fraction2& fraction)
        // Initialize our members using the corresponding member of the parameter
        : m_numerator{ fraction.m_numerator }
        , m_denominator{ fraction.m_denominator }
    {
        std::cout << "Copy constructor called\n"; // just to prove it works
    }

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};


/* Pass by value will implicitly invoking the copy constructor
*/

void printFraction(Fraction2 f) // f is pass by value
{
    f.print();
}

void func2()
{
    Fraction2 f2 { 5, 3 };
    printFraction(f2); // f is copied into the function parameter using copy constructor

}


/* Return by value and the copy constructor
*/

Fraction2 generateFraction(int n, int d)
{
    Fraction2 f{ n, d };
    return f;
}

void func3()
{
    Fraction2 f3 { generateFraction(5, 3) }; // 2 copy constructors are called here, one for the return value and one for the initialization of f3
                                                  // but you may see only one/no copy constructor call because of copy elision
}


/* Copy elision

- Since the compiler is free to rewrite statements to optimize them, 
  the compiler can optimize away the unnecessary copy constructor calls.
  we say the constructor has been elided.

- Prior to C++17, copy elision was strictly optional. In C++17, copy elision became 
  mandatory in some cases (even if you tell your compiler not to perform copy elision).
*/


/* Using = default to generate a default copy constructor
*/

class Fraction3
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    Fraction3(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    // Explicitly request default copy constructor
    Fraction3(const Fraction3& fraction) = default;
};


/* Using = delete to prevent copies
*/

class Fraction4
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    Fraction4(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    // Delete the copy constructor so no copies can be made
    Fraction4(const Fraction4& fraction) = delete;
};


int main()
{
    // Copy constructor
    func1();


    // Pass by value will implicitly invoking the copy constructor
    func2();


    // Return by value and the copy constructor
    func3();


    return 0;
}

/* References

- https://www.learncpp.com/cpp-tutorial/introduction-to-the-copy-constructor/
- https://www.learncpp.com/cpp-tutorial/class-initialization-and-copy-elision/
*/