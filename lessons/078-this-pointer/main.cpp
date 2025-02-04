/* "this" pointer

- Inside every member function, the keyword "this" is a const pointer that holds 
  the address of the current implicit object.
    ```
    void print() const { std::cout << m_id; }       // implicit use of this
    void print() const { std::cout << this->m_id; } // explicit use of this
    ```
*/

#include <iostream>

class Simple
{
private:
    int m_id{};

public:
    Simple(int id)
        : m_id{ id }
    {
    }

    int getID() const { return m_id; }
    void setID(int id) { m_id = id; }

    void print() const { std::cout << this->m_id; } // use `this` pointer to access the implicit object and operator-> to select member m_id
};

int main()
{
    Simple simple{1};
    simple.setID(2);

    simple.print();

    return 0;
}

/*
- When compiled, the compiler rewrites:
    - `simple.setID(2);` to `Simple::setID(&simple, 2);`
    - `void setID(int id) { m_id = id; }` to `static void setID(Simple* const this, int id) { this->m_id = id; }`
*/


/*
- Some developers prefer to explicitly add this-> to all class members to make it clear that they are referencing a member. 
  We recommend that you avoid doing so, and use the “m_” prefix instead.
*/


/* Method chaining by returning *this

For example:
```
Calc calc{};
calc.add(5).sub(3).mult(4); // method chaining
```
*/


/* Resetting a class back to default state

by creating a new object using default constructor and then assigning it to the implicit object:
```
void reset()
{
    *this = {}; // value initialize a new object and overwrite the implicit object
}
```
*/


/* Explain why a const object cannot call non-const member functions

- For a non-const member function, `this` is a const pointer to a non-const value.
- When we call a non-const member function on a const object, the passed argument is a const pointer to a const object.
- Calling that function requires discarding the const qualifier, which cannot be done implicitly.
*/

/* Why this a pointer and not a reference

- The answer is simple: when this was added to C++, references didn’t exist yet.
- In Java and C#, `this` is implemented as a reference.
*/

/* References

- https://www.learncpp.com/cpp-tutorial/the-hidden-this-pointer-and-member-function-chaining/
*/