// https://www.learncpp.com/cpp-tutorial/introduction-to-literals-and-operators/


/* Operators by "arity":

- Unary operators: act on 1 operand. E.g, -5.
- Binary operators: act on 2 operands. E.g, 5 + 3.
- Ternary operators: act on 3 operands. E.g, a ? b : c.
- Nullary operators: act on 0 operands.

*/

/* Chaining operators and Return values

- Most operators in C++ calculates a return value. Few operators that do not produce return values (such as delete and throw).

- Some operators are primarily called for their return values (e.g, +, -). There return values are usually obvious.
- Some operators called for their side effects (e.g, =, <<). There return values are not always obvious.
    + For example, operator= and operator<< return their left operand.
      So `x = 5` returns x, and `std::cout << x` returns std::cout.
      This allows chaining of operators. For example, `std::cout << 5 << 6` is equivalent to
      `(std::cout << 5) << 6`, because the return value of `std::cout << 5` is `std::cout`.
      `x = y = 5` is equivalent to `x = (y = 5)`, because the return value of `y = 5` is `y`.

*/

#include <iostream>

int main()
{
    int x{ 1 };
    int y{ 2 };
    int z{  };
    int max{  };

    // comma operator
    std::cout << (++x, ++y) << '\n'; // increment x and y, evaluates to the right operand
    // Avoid using the comma operator, except within for loops.
    
    // Note that comma has the lowest precedence of all the operators, even lower than assignment. 
    z = (x, y); // evaluate (a, b) first to get result of b, then assign that value to variable z.
    z = x, y; // evaluates as "(z = a), b", so z gets assigned the value of a, and b is evaluated and discarded.

    // conditional operator
    max = ((x > y) ? x : y);
    std::cout << (x < 0) ? "negative" : "non-negative"; // you might expect this to print "non-negative", but it prints "0"
    // because operator<< has higher precedence than operator?:

    std::cout << (true ? 1 : 2) << '\n';    // okay: both operands have matching type int
    std::cout << (false ? 1 : 2.2) << '\n'; // okay: int value 1 converted to double
    std::cout << (true ? -1 : 2u) << '\n';  // surprising result: -1 converted to unsigned int, result out of range
    std::cout << ((x != 5) ? x : "x is 5"); // compile error: compiler can't find common type for constexpr int and C-style string literal

    return 0;
}

/* References

- https://www.learncpp.com/cpp-tutorial/the-comma-operator/
- https://www.learncpp.com/cpp-tutorial/the-conditional-operator/

*/