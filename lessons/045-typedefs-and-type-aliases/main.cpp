/* Type aliases

- `using` keyword
- does not actually define a new, distinct type.
*/

/* Typedefs

- an older way of creating an alias for a type
- Prefer type aliases over typedefs.
*/

/* Type aliases use cases

- platform independent coding
- make complex types easier to read


*/

#include <iostream>

// platform independent coding
#ifdef INT_2_BYTES
using int16_t = int;
#else
using int16_t = short;
#endif

int main()
{
    using Distance = double; // type alias
    Distance milesToDestination{ 3.4 };


    typedef double Distance2; // typedef
    Distance2 milesToDestination2{ 3.4 };

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/typedefs-and-type-aliases/
*/