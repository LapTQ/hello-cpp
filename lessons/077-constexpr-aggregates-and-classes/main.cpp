/* Constexpr aggregates and Constexpr member functions
*/

#include <iostream>

struct Pair // Pair is an aggregate
{
    int m_x {};
    int m_y {};

    constexpr int greater() const
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};


/* Constexpr class objects and constexpr constructors

- When we compile this program, we get a compiler error about Pair2 not being a “literal type”.
  this is because the constructor function in our Pair2 class is not constexpr.

- The definition of a literal type is complex, so we won’t go into it here.
*/

class Pair2 // Pair is no longer an aggregate
{
private:
    int m_x {};
    int m_y {};

public:
    Pair2(int x, int y): m_x { x }, m_y { y } {}

    constexpr int greater() const
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};

class Pair3
{
private:
    int m_x {};
    int m_y {};

public:
    constexpr Pair3(int x, int y): m_x { x }, m_y { y } {} // now constexpr

    constexpr int greater() const
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};


/* Constexpr member functions are no longer implicitly const since C++14)

=> Constexpr non-const member functions can change data members.
*/


int main()
{
    // Constexpr aggregates and Constexpr member functions
    constexpr Pair p { 5, 6 };        // now constexpr
    std::cout << p.greater() << '\n'; // p.greater() evaluates at runtime or compile-time

    constexpr int g { p.greater() };  // p.greater() must evaluate at compile-time
    std::cout << g << '\n';


    // Constexpr class objects and constexpr constructors
    constexpr Pair2 p2 { 5, 6 };       // compile error: p2 is not a literal type
    constexpr Pair3 p3 { 5, 6 };       // okay, p3 is a literal type

    return 0;
}


/* Clarify: We can use non-const object to initialize a constexpr object.

- If this breaks your brain, it’s probably because you haven’t fully separated const from constexpr.
- There is no requirement that a constexpr variable be initialized with a const value.
  It may seem that way because most of the time we initialize constexpr variable using literals (which are const)
  and because the terms const and constexpr have similar names.
*/


/* Constexpr functions that return const references (or pointers)

Let's see a member function:
```
constexpr const int* const getXPtr() const { return &m_x; }
```
That’s a lot of const-ing!

- The constexpr indicates that the member function can be evaluated at compile-time. 
- The 1st const int& is the return type of the function.
- The 2nd const indicates a pointer to const. 
- The 3rd const means the member-function itself is const so it can be called on const objects.
*/


/* References

- https://www.learncpp.com/cpp-tutorial/constexpr-aggregates-and-classes/
*/