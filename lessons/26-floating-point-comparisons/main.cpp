/* Comparing floating point values using any of the relational operators (<, >, <=, >=, ==, !=) can be dangerous.

- There is one notable exception: compare a floating point "literal" with a "variable of the same type" that has been initialized with a "literal of the same type", 
  so long as the number of significant digits in each literal does not exceed the minimum precision for that type.
- It is generally not safe to compare floating point literals of different types.
*/

/* Comparing floating point numbers

- New developers often try to write their own “close enough” function using a epsilon.
  While this function can work, it’s not great:
  ++ e.g., if epsion is 1e-5, then 0.0000001 and 0.00001 would be the same.
- Donald Knuth, a famous computer scientist suggested the following method in his book “The Art of Computer Programming".
  But it is not perfect: fail when the numbers approach zero.
*/

#include <iostream>
#include <algorithm> // for std::max
#include <cmath>     // for std::abs

// Donald Knuth
bool approximatelyEqualRel(double a, double b, double relEpsilon)
{
	return (std::abs(a - b) <= (std::max(std::abs(a), std::abs(b)) * relEpsilon));
}
// if we want to say “close enough” means a and b are within 1% of the larger of a and b, we pass in an relEpsilon of 0.01


bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon)
{
    // Check if the numbers are really close -- needed when comparing numbers near zero.
    if (std::abs(a - b) <= absEpsilon)
        return true;

    // Otherwise fall back to Knuth's algorithm
    return approximatelyEqualRel(a, b, relEpsilon);
} // should be good enough to handle most cases you’ll encounter.

int main()
{
    constexpr double d1{ 100.0 - 99.99 }; // should equal 0.01 mathematically
    constexpr double d2{ 10.0 - 9.99 }; // should equal 0.01 mathematically

    if (d1 == d2)
        std::cout << "d1 == d2" << '\n';
    else if (d1 > d2)
        std::cout << "d1 > d2" << '\n'; // this is the output
    else if (d1 < d2)
        std::cout << "d1 < d2" << '\n';

    std::cout << std::boolalpha << (0.3 == 0.2 + 0.1) << "\n"; // prints false


    constexpr double gravity { 9.8 }; // variable of type double, initialized with a literal of the same type
    std::cout << (gravity == 9.8) << "\n"; // compare with a literal of the same type => safe
    std::cout << (gravity == 9.8f) << "\n"; // print "false"

    // Donald Knuth is not perfect
    constexpr double a { 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 };
    std::cout << approximatelyEqualRel(a, 1.0, 1e-8) << '\n'; // prints true
    std::cout << approximatelyEqualRel(a - 1.0, 0.0, 1e-8) << '\n'; // prints false
    
    // good enough
    std::cout << approximatelyEqualAbsRel(a, 1.0, 1e-12, 1e-8) << '\n';     // compare "almost 1.0" to 1.0
    std::cout << approximatelyEqualAbsRel(a-1.0, 0.0, 1e-12, 1e-8) << '\n'; // compare "almost 0.0" to 0.0

    return 0;
}

/* References

- https://www.learncpp.com/cpp-tutorial/relational-operators-and-floating-point-comparisons/
*/