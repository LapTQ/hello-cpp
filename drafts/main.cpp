#include <iostream>

class Foo
{
private:
    int m_x{};
public:
    Foo(int x)  // allow implicit conversion from int to Foo
        : m_x{ x }
    {
    }

    int getX() const { return m_x; }
};

void printFoo(Foo f) // has a Foo parameter
{
    std::cout << f.getX() << '$';
}

void printFoo(int f) // has a Foo parameter
{
    std::cout << f << '\n';
}

int main()
{
    printFoo(5); // we're supplying an int argument => conversion from `5` to `Foo { 5 }`
    // In C++17 onward, the copy is mandatorily elided. 
    // Parameter f is copy initialized with value 5, and no call to the copy constructor is required.

}