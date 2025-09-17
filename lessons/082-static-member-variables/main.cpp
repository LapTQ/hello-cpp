/*  Static member variables

- "static member variables" are shared by all objects of the class.
- static member exists independently of any class objects.
- Static members are global variables that live inside the scope region of the class.
*/


/* you "must explicitly" define (and optionally initialize) the static member outside of the class, in the global scope.
(with 2 exceptions discussed shortly)

- Note: differentiating between "declare" and "define"

- This is because, static member variables are essentially global variables, so you must define them in the global scope.
*/

class Something
{
public:
    static int s_value; // declare
};

int Something::s_value{ 1 }; // define and initialize
// If no initializer is provided, static member variables are zero-initialized by default

void func1()
{
    // static member s_value exists independently of any class objects
    Something::s_value = 2;
}


/* Defining static member variables and header files

- If the class is defined in a header file:
    + the static member definition is usually placed in the associated .cpp file.
    + Or, the static member definition can be defined as `inline` and placed below the class definition in the header file.
- If the class is defined in a .cpp file:
    + the static member definition is usually placed below the class definition in the .cpp file.
*/


/* Define static member variables inside the class definition

There are 2 exceptions to the rule that static member variables must be defined outside of the class:
    + when the static member is a constant integral type or const enum
    + when the static member is inline
      (Note: constexpr members are implicitly inline)

Best practice:
- Make your static members inline or constexpr so they can be initialized inside the class definition.
*/

class Whatever
{
public:
    static const int s_value{ 4 }; // okay, constant integral type or const enum
    static inline int s_value2{ 4 }; // okay, inline
    static constexpr int s_value3{ 4 }; // okay, constexpr members are implicitly inline
};


int main()
{
    func1();
    
    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/static-member-variables/
*/