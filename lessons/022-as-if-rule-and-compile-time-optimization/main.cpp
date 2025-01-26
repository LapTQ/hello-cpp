/* Introduction

- Profiler: a program used to measure running time and performance.
- Because hand-optimization is slow, programmers typically focuses on 
  making high-level improvements that will have a large impact.
- Other kinds of optimization can be performed automatically. A program that 
  optimizes another program is called an optimizer.
- Optimizers typically work at a low-level, looking for ways to improve 
  statements or expressions by rewriting, reordering, or eliminating them. 
- For example, when you write i = i * 2;, the optimizer might rewrite this 
  as i *= 2;, i += i;, or i <<= 1;. one might be faster than the others on a 
  given architecture. A programmer would probably not know which is the most 
  performant choice.
- Most compilers default to no optimization, so if you’re using a command-line 
  compiler, you’ll need to enable optimization yourself. See: https://www.learncpp.com/cpp-tutorial/configuring-your-compiler-build-configurations/#:~:text=For%20gcc%20and%20Clang%20users
*/

/* The as-if rule

- The as-if rule says: the compiler can modify a program however it likes 
  so long as those modifications do not affect a program’s “observable behavior”.
*/

/* An optimization opportunity

int x { 3 + 4 };

- If this program were compiled exactly as it was written (with no optimizations), 
  the compiler would calculates 3 + 4 at runtime. If the program were executed a million times,
  re-calculating every time is wasteful.
=> Compile-time evaluation

- In this lesson we will look at some simple optimization techniques that make use of compile-time evaluation.
*/

/* Constant folding

- the compiler would recognize that the expression 3 + 4 has constant operands, and then replace the expression with the result 7.
*/

/* Constant propagation

int x { 7 };
std::cout << x << '\n';

- value 7 will be stored in the memory allocated for x.
- the program will go out to memory again to fetch the value 7 so it can be printed. 
- This requires two memory access operations (one to store the value, and one to fetch it).
*/

/* Dead code elimination

int x { 7 };
std::cout << 7 << '\n';
return 0;

- x is defined and initialized, but it is never used anywhere.
- Dead code elimination would remove the definition of x.
*/

/* Const variables are easier to optimize

const int x { 7 }; // x is now const
*/

/* Optimization can make programs harder to debug

- For example, if you try to watch a variable that has been optimized out, the debugger won’t be able to locate the variable.
*/

/* Compile-time constants vs runtime constants

- A compile-time constant is a constant whose value is known at compile-time.
- A runtime constant is a constant whose value is determined in a runtime context.
- However, in C++ these definitions are not all that useful:
  ++ Some runtime constants (and even non-constants) can be evaluated at compile-time.
  ++ Some compile-time constants (e.g. const double d { 1.2 };) cannot be used in compile-time features.
*/

#include <iostream>

int five()
{
    return 5;
}

int pass(const int x) // x is a runtime constant
{
    return x;
}

int main()
{
	int x { 3 + 4 }; // constant folding -> int x { 7 };
    // later dead code elimination

	std::cout << x << '\n'; // constant propagation -> std::cout << 7 << '\n';


    // The following are non-constants:
    [[maybe_unused]] int a { 5 };

    // The following are compile-time constants:
    [[maybe_unused]] const int b { 5 };
    [[maybe_unused]] const double c { 1.2 };
    [[maybe_unused]] const int d { b };       // b is a compile-time constant

    // The following are runtime constants:
    [[maybe_unused]] const int e { a };       // a is non-const
    [[maybe_unused]] const int f { e };       // e is a runtime constant
    [[maybe_unused]] const int g { five() };  // return value isn't known until runtime
    [[maybe_unused]] const int h { pass(5) }; // return value isn't known until runtime

	return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/the-as-if-rule-and-compile-time-optimization/
*/