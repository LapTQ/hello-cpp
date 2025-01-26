/* Introduction

- Different data types may represent the “same” number differently. For example:
  ++ integer value 3 might be stored as binary `0000 0000 0000 0000 0000 0000 0000 0011`.
  ++ loating point value 3.0 might be stored as binary `0100 0000 0100 0000 0000 0000 0000 0000`.

- when
float f{ 3 };
it needs to convert the integer 3 to 3.0 before storing it in f.
*/

/* The standard conversions

4 categories:
+ Numeric promotions
+ Numeric conversions
+ Arithmetic conversions 
+ Other conversions

- When a type conversion is needed, the compiler will see if there are standard conversions 
  that it can use.
- The compiler may apply zero, one, or two standard conversions in the conversion process.
*/

/* Numeric promotions

- is the type conversion of certain narrower numeric types (such as a char) 
  to certain wider numeric types (typically int or double) 
  that can be processed "efficiently".
- Including:
  ++ floating point promotions:
    * float -> double
  ++ integral promotions
    * signed char, signed short -> int
    * unsigned char, char8_t, unsigned short -> int if int can represent all values of the original type, otherwise unsigned int
    * bool -> int, with false becoming 0 and true becoming 1

- Not all widening conversions (such as char to short, or int to long) are numeric promotions.
  They are numeric conversions because they do not assist converting "efficiently".


Advantages:
- All numeric promotions are value-preserving, and thus “safe”.
- Numeric promotion reduces redundancy.
  E.g., you can define `void printInt(int x)` and pass short, char, or bool to it
  without having to define `void printShort(short x)`, `void printChar(char x)`, and `void printBool(bool x)`.
*/

/* Numeric conversions

5 basic types:
- integral type -> any integral type (excluding integral promotions)
- floating point type -> any floating point type (excluding floating point promotions)
- floating point type -> any integral type
- integral type -> any floating point type
- integral type or floating point type -> bool

- Numeric conversions fall into 3 categories:
  ++ Value-preserving conversions:
     - The compiler will not raise warnings.
     - the destination type can represent all values of the source type.
     - can be converted back to the source type without loss of information. E.g., int -> long -> int.
  ++ Reinterpretive conversions:
     - The compiler might not raise warnings.
     - the destination type cannot represent all values of the source type.
     - can be converted back to the source type without loss of information. E.g., int -> unsigned int -> int.
  ++ Lossy conversions: E.g., int -> float -> int.
     - The compiler will raise warnings.
*/

/* Arithmetic conversions

??? y { 2 + 3.5 };

- In C++, certain operators require that their operands be of the same type. 
- If one of these operators is invoked with operands of different types,
  one or both of the operands will be implicitly converted to "common type" using "usual arithmetic conversions".
- ...
*/

#include <iostream> 

void someFcn(int i)
{
}

int main()
{
    double d{ 5.0 };

    someFcn(d); // bad: implicit narrowing conversion will generate compiler warning

    // good: Make intentional narrowing conversions explicit
    someFcn(static_cast<int>(d)); // no warning generated



    int i{ 2 };
    std::cout << typeid(i).name() << '\n'; // show us the name of the type for i
    std::cout << typeid(d).name() << '\n'; // show us the name of the type for d
    std::cout << typeid(i + d).name() << ' ' << i + d << '\n'; // show us the type of i + d

    std::cout << typeid(5u-10).name() << ' ' << 5u - 10 << '\n'; // 5u means treat 5 as an unsigned integer
    // you might expect the result to be -5, but it's not: 10 is converted to an unsigned int, then 5 - 10 = -5 is out of range for an unsigned int
    std::cout << std::boolalpha << (-3 < 5u) << '\n';
    // you might expect the result to be true, but it's false: -3 is converted to a large an unsigned int.

    return 0;
}

/* Make intentional narrowing conversions explicit
*/

/* Brace initialization disallows narrowing conversions

For example:
int i { 3.5 }; // won't compile


However, some constexpr conversions aren’t considered narrowing. For example:

constexpr int n2 { -5 };
unsigned int u2 { n2 };  // compile error
// conversion is narrowing (and thus disallowed by list-initialization) because:
// + although n2 is constexpr,
// + -5 cannot be represented exactly by an unsigned int

constexpr int n1{ 5 };
unsigned int u1 { n1 };  // okay, 
// conversion is not narrowing (and thus allowed by list-initialization) because:
// + n1 is constexpr, and
// + 5 can be represented exactly by an unsigned int

But strangly, conversion from a floating point type to an integral type is always 
considered narrowing, even if the value can be represented exactly.
int n { 5.0 }; // compile error: narrowing conversion

Even more strangely, conversion from a floating point type to a narrower floating
point type is not considered narrowing despite loss of precision:
constexpr double d { 0.1 };
float f { d }; // not narrowing, even though loss of precision results

- 
*/


/* References

- https://www.learncpp.com/cpp-tutorial/implicit-type-conversion/
- https://www.learncpp.com/cpp-tutorial/numeric-conversions/
- https://www.learncpp.com/cpp-tutorial/narrowing-conversions-list-initialization-and-constexpr-initializers/
*/