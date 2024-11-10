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