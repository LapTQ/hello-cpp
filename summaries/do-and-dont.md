

## Print newline

* ✅ Use character `"\n"`:
* ❌ Avoid using `std::endl`. It flushes the buffer, which is slower.

## Comma operator

* ❌ Avoid using **comma operator**, except in `for` loops:
```C++
std::cout << (++x, ++y) << '\n'; // evaluates left and right, then retuns the right operand
```


## Macro

* ✅ Can use `#if 0` to comment out a large block of code that contains **multi-line comments**. Change it to `#if 1` when needed.
* ❌ Avoid using **object-like macros with substitution text**, as better methods are available.


## `#include` and header files

* ❌ Avoid `#including` .cpp files.
* Including header files from other directories:
    * ❌ Avoid using relative path (e.g, `#include "headers/myHeader.h"`).
    * ✅ Instead, tell your compiler about other locations to search for (e.g., `-I./lessons/11-header-files/others`).
* ✅ To maximize the chance that missing includes will be flagged by compiler, order your `#includes` as follows:
    1. the paired header file (`add.cpp` and `#include "add.h"`)
    2. other headers from same project
    3. 3rd party lib headers
    4. standard lib headers
* ✅ Always have a **header guard** in a header file to avoid violating ODR from having **a** code file #include a header (which may contain **definition**) multiple time. 
    * ⚠️ However, header guards do not prevent **multiple** code file `#include` the same header.
* ❌ Don't use `#pragme once`. Use header guard instead.
* ✅ Use a complex name for your header guard (e.g., `PROJECT_PATH_FILE_H`). This is to avoid case where 2 separated header files (e.g., `A/config.h` and `B/config.h`) might have the same name of header guard (e.g., `CONFIG_H`).


## Debugging

* ✅ use `std::cerr` (not buffered) instead of `std::cout` (may be buffered).
* To enable/disable debugging mode:
    * 👍 Solution 1: Conditionalizing your debugging code with macro: `#define ENABLE_DEBUG` in a header file and `#include` it everywhere. But ensure that you're not misspell `ENABLE_DEBUG` or forgot `#include` the header file.
    * 👍 Use `plog` logger. ❌ Don't use `std::clog` logger.


## Data types

* ❌ Avoid using unsigned types.
* ❌ Avoid `short`, `long`, fast/least integral types (prefer a fixed-width integer type instead).
* ❌ Avoid 8-bit fixed-width integer types (prefer a 16-bit fixed-width integer type instead).
* ❌ Avoid `long double`.
* ⚠️ `std::int8_t` and `std::uint8_t` likely behave like `signed char` and `unsigned char` instead of integers.


### Input text

* To read whitespace characters (type `char`):
    * ❌ can't use `std::cin >>`
    * ✅ use `std::cin.get(ch)`
* To read a line (including whitespace):
    * ❌ don't use `std::cin >>`
    * ✅ use `std::getline()`


## Compile-time optimization

* ✅ Most compilers default to no optimization, so if you’re using a command-line 
  compiler, you’ll need to enable optimization yourself.


## Using `std:string` and `std::string_view`

* ✅ To view a substring of a string, use `std::string_view` with `.remove_prefix()` and `.remove_suffix()`.
* Initialize a `std::string_view`:
    * ❌ Don't initialize with a `std::string` **literal**. Because, the temporary `std::string` literal will be destroyed at the end of the statement:

        ```C++
        std::string_view name { "Alex"s }; // "Alex"s creates a temporary std::string
        std::cout << name << '\n'; // undefined behavior
        ```
    * 👍 It's okay to initialize with a C-style string **literal** or a `std::string_view` **literal**. Because, C-style string literals exist for the entire program.
* ⚠️ Returning a string in a function that has return type `std::string_view`: 2 main cases when this can be done safely:
    * 👍 when the returned object is a C-style string literals:

        ```C++
        std::string_view getBoolName(bool b)
        {
            return "false";
        }
        ```
    * 👍 when the returned object is a function parameter of type `std::string_view`:

        ```C++
        std::string_view firstAlphabetical(std::string_view s1, std::string_view s2)
        {
            if (s1 < s2)
                return s1;
            return s2;
        }
        ```


## Comparing floating point values

* ❌ It's very dangerous to compare floating point values directly using relational operators (<, >, <=, >=, ==, !=).
    
    👍 One exception: compare a floating point **literal** with a **variable of the same type** that has been initialized with a **literal of the same type**.
* ❌ It's generally not safe to compare floating point values of **different** types.


## `goto` statement

* ❌ Avoid using `goto` statement.
* ✅ Exception: when you need to exit a nested loop.


## Pseudo-random number generation

* 👍 For most applications, Mersenne Twister is fine. However, by modern PRNG standards, Mersenne Twister is a bit outdated.
* ✅ For highest/fastest quality random results, consider:
    * The Xoshiro family and Wyrand for non-cryptographic PRNGs.
    * The Chacha family for cryptographic (non-predictable) PRNGs.


## Constant expressions

* ✅ Constexpr/consteval functions should be defined in a header file.
* ✅ If you want to force a constexpr function to be evaluated at compile time, use `consteval` with a helper function:
    ```C++
    consteval auto compileTimeEval(auto value) { return value; }

    constexpr int greater2(int x, int y) { return (x > y ? x : y); }

    int main()
    {
        compileTimeEval(greater2(3, 4)); // will be evaluated at compile time
    }
    ```
* ❌ C++ does not currently provide any reliable mechanisms to notify you if a function is being evaluated at compile time or runtime.


## Namespaces

* ✅ Naming convention: Company or org :: project or library :: module (e.g. `Foosoft::Foologger::Lang`)
* ✅ Prefer defineing global variables inside a namespace rather than in the global namespace.
* ❌ Do not use using-statements in header files.
* ❌ Do not use using-statements before an #include directive.
* ✅ If you want to version your code, you can use **inline namespaces**.


## Linkage

* ✅ If you want to make all declarations to have internal linkage without having to use `static` keyword, you can put them in an unnamed namespace.
    

## Share variables across multiple files

* Global **constants**:
    * 👍 Solution 1: Global constants as internal variables
        1. Create a header file and define a namespace in it.
        2. Put the global constants inside the namespace, make it `constexpr`.
        3. `#include` the header file wherever you need.

        👍 Simple
        
        👎️ Changing in the header file will require recompiling all files that include it.
        
        👎️ Each translation unit get its own copy of the constants => use more memory.
    * 👍 Solution 2: Global constants as external variables
        1. Create a .cpp file and define a namespace in it.
        2. Put the global constants inside the namespace, make it `extern constexpr`.
        3. Create a header file and forward declare the global constants.
        4. `#include` the header file wherever you need.

        👍 Changing the constant only require recompiling the .cpp file.
        
        👎️ Because forward declarations can’t be constexpr, the constant cannot be used in constant expression outside of the .cpp file which defines the constant.
    * ✅ Solution3: Global constants as inline variables:
        1. Create a header file and define a namespace in it.
        2. Put the global constants inside the namespace, make it `inline constexpr`.
        3. `#include` the header file wherever you need.

        👍 The constants will only be instantiated once and shared across all code files (linker will de-duplicate definition).
        
        👍 Can be used in constant expressions in any translation unit.
        
        👎️ Changing in the headeer file will require recompiling all files that include it.


## Assertion

* ✅ Favor `static_assert` over `assert()` whenever possible.


## Explicit type conversion

* ✅ Use `static_cast` for most type conversions.
* ❌ Do not use C-style casts: e.g., `(int) x`.
* ❌ Do not use const cast and reinterpret cast unless you have a very good reason.


## Type deduction

* ✅ Can use **trailing return type syntax** to make code more readable and dynamic. E.g., this function has return type based on its parameter types: `auto add(int x, double y) -> std::common_type_t<decltype(x), decltype(y)>;`
* ✅ Use `auto*` instead of `auto` for type deduction with pointers. It's more clear and *less error-prone*.

    ```C++
    int* x;

    // auto => order not matter
    const auto y { x }; // int* const (a const pointer)
    auto const y { x }; // int* const (a const pointer)

    // auto* => order matters
    const auto* y { x }; // const int* (a pointer to const)
    auto* const y { x }; // int* const (a const pointer)
    ```


## Function templates

* ✅ Use non-type template parameters to when we need to pass constexpr values to functions/class types. For example, to `static_assert` at compile time.
* Function templates in multiple files:
    * ❌ A forward declaration of the function template is not enough:
    
        ```C++
        // add.h
        template <typename T>
        T add(T x, T y);
        
        // add.cpp => assume that the function template is defined here
        // ...

        // main.cpp
        #include "add.h"
        int main()
        {
            add(1, 2);
            return 0;
        }
        ```

        Linker error: 
        * When compiling `main.cpp`, it assumes that `addOne<int>` exists elsewhere and will be linked in later.
        * When compile `add.cpp`, there is no uses of this template so the compiler will not instantiate anything.
    * ✅ Put all the template code in a header (.h) file instead of a source (.cpp) file. It does not violate the ODR (because functions implicitly instantiated from templates are implicitly inline).


## Pointers

* ✅ Use `nullptr` for null pointers. ❌  Don't use `NULL` or `0`.


## Passing arguments to functions

* ✅ It's okay to pass fundamental types by value. They are cheap to copy. Don't pass by reference unless you need to modify the argument.
* ✅ It's okay pass class types by reference (or const reference). Binding a reference is always cheap.
* ⚠️ Don't pass a `std::string` to a function by value. Because, it will make an expensive copy.
* ✅ It's okay to pass a `std::string_view` by value for read-only access purpose. It's cheap. For function parameters, prefer `std::string_view` over `const std::string&` in most cases (whatever the passed argument is `std::string`, `std::string_view`, or C-style string).
* ⚠️ When passing by reference, ensure the type of the argument matches the type of the parameter. Otherwise, it will results in an unexpected (and possibly expensive) type conversion.
* ✅ It's okay to pass by address. Copying a pointer is always cheap.
* ✅ It is okay to return `std::vector` and `std::string` by value, because they support move semantics and will **automatically** invoke move semantics when **returning by value**. (Such types should still be passed by const reference).
* ✅ => For move-capable types, we prefer to pass by const reference, and return by value.



## Returning values from functions

* ✅ When your function may or may not return a value of type `T`:
    * Use `std::optional<T>` if `T` would normally be passed by value.

    This is because `std::optional` has value semantics: local objects are copied.


## Program-defined types: Enumerated types

* ✅ It's okay to pass enumerations by value. They are small and cheap to copy.
* ✅ Favor scoped enumerations over unscoped enumerations.
* For **unscoped enumerations**, 
    * ✅ Put the unscoped enumerated type inside a namespace to avoid name collisions.
    * ✅ It's recommended to add an "invalid" or "unknown" enumerator with value 0 to avoid semantically invalid enumeration when it's zero-initialized:

        ```C++
        enum Animal
        {
            unknown = 0, // default value (0)
            cat,
            dog,
        };
        ```
    * ❌ Not safe:

        ```C++
        enum Color { red, };
        enum Fruit { banana, };
        Color color { red };
        Fruit fruit { banana };
        std::cout << std::boolalpha << (color == fruit) << '\n'; // true, compare as integers
        ```


## Program-defined types: Class types

* ✅ When adding a new member variable to a struct, put it at the end to avoid breaking existing code. Because, struct initializes its members in the order they are declared.
* ✅ Always provide default values for your members (inside the class type definition).
* Getter:
    * ✅ Make getter `const`, so they can be called on both const and non-const objects.
    * ✅ Getters should return *by value* or by *const lvalue reference*.
* ❌ Don't use `( )` for initialization
* ✅ You can do method chaining by returning `this`: `calc.add(5).sub(3).mult(4);`
* ✅ You can reset a class back to default state by using `this` and default constructor:

    ```C++
    void reset()
    {
        *this = {}; // value-initialize a new object and overwrite the implicit object
    }
    ```


## Program-defined types and header files

* ✅ A program-defined type used in multiple code files should be defined in a header file with the same name as the program-defined type and then `#included` into each code file as needed.
* ✅ For non-template classes:
    * put your class definitions in a header file with the same name as the class, and
    * define non-trivial member functions outside of the class and in a .cpp file with the same name as the class, and
    * define trivial member functions (such as access functions, constructors with empty bodies, etc…) inside the class definition.

    For example:

    `Day.h`:
    ```C++
    #ifndef DAY_H
    #define DAY_H

    class Day
    {
    private:
        int m_day{};

    public:
        Day(int day);
        void print() const;
    };

    #endif
    ```

    `Day.cpp`:
    ```C++
    #include "Day.h"

    Day::Day(int day) // constructor definition
        : m_day{ day }
    {
        // ...
    }

    void Day::print() const // print function definition
    {
        std::cout << "Day(" << m_day << ")\n";
    };
    ```
    
    Note that that .cpp file also needs to be compiled into any project that uses the header file so that the linker can connect calls to the member functions to their definitions.
* For template classes:
    * ❌ Simply putting the class definition in a header file, and the member function definitions in a similarly named .cpp file will not work.
    * ✅ Solution 1: Put the entire template class in a header file.

        👎️ Increase your compile and link times.
    * ✅ Solution 2: Move the contents of .cpp to a new file named .inl, and include the .inl file at the end of the header file (inside the header guard).

        👎️ Same result as solution 1.

        👍 Keep things a little more organized.
    * ✅ Solution 3: Use an explicit instantiation file. For example: `Array.h`, `Array.cpp`, and `templates.cpp`:

        `templates.cpp`:
        ```C++
        // Ensure the full Array template definition can be seen
        #include "Array.h"
        #include "Array.cpp" // we're breaking best practices here, but only in this one place

        // #include other .h and .cpp template definitions you need here

        template class Array<int>; // Explicitly instantiate template Array<int>
        template class Array<double>; // Explicitly instantiate template Array<double>
        ```

        The `template class` command causes the compiler to explicitly instantiate the template class.

        👍 More efficient.
        
        👎️ Requires more files.

* Static member variables:
    * If the class is defined in a header file:
        * ✅ define the static member variables in the associated .cpp file, or
        * ✅ define it as `inline` and place it below the class definition in the header file.
    * If the class is defined in a .cpp file:
        * ✅ define it below the class definition in the .cpp file.
    * 👍 Make your static members variables inline or constexpr so they can be initialized inside the class definition.
    * ✅ To access a **private** static member variable, you can create a static member function.
        ```C++
        class Something
        {
        private:
            static inline int s_value { 1 };

        public:
            static int getValue() { return s_value; } // static member function
        };
        ```

## Containers and arrays

* `std::vector`
    * ❌ Don't use unsigned integral type as index:
        ```C++
        for (std::size_t index{ arr.size() - 1 }; index >= 0; --index) // index is unsigned
        ```
        When we decrement index when it has value 0, it will wrap around to a large positive value.
    * Solution 1: use signed integral type for index:
        * ✅ For not very large array, `int` should be fine:
            ```C++
            int length{ static_cast<int>(arr.size()) }; // cast to int
            for (int index{ length - 1}; index >= 0; --index) // index is signed
            {
                std::cout << arr[static_cast<std::size_t>(index)] << ' ';   // cast to std::size_t
            }
            ```
        * ✅ For very large array, use the strangely named `std::ptrdiff_t`. This typedef is often used as the signed counterpart to `std::size_t`.
            ```C++
            using Index = std::ptrdiff_t;
            auto length{ static_cast<Index>(arr.size()) }; // cast to Index
            for (auto index{ length - 1}; index >= 0; --index) // index is signed
            {
                std::cout << arr[static_cast<std::size_t>(index)] << ' ';   // cast to std::size_t
            }
            ```
        * ✅ (C++20) Use `std::ssize()` to get the signed size:
            ```C++
            auto length{ std::ssize(arr) }; // cast to Index
            for (auto index{ length - 1 }; index >= 0; --index) // index is signed
            {
                std::cout << arr[static_cast<std::size_t>(index)] << ' ';   // cast to std::size_t
            }
            ```
        * 👎️ Using `static_cast` every time you use the index is hard to read. Consider:
            * Use a conversion function with a short name.
            * Use a custom view (Similar to `std::string_view` is a view into a string) by overloading operator[].
            
            (See syntax-and-snippnet.md)
    * Solution 2: Index the underlying C-style array instead. 
        ✅ This method is the best of the indexing options.
        ```C++
        auto length { static_cast<Index>(arr.size()) };
        for (auto index{ length - 1 }; index >= 0; --index) // index is signed
        {
            std::cout << arr.data()[index] << ' ';
        }
        ```
    * ✅ Consider using range-based for loop to traverse a container instead of explicit indexing.
    * ❌ Don't use `std::vector<bool>`.
        
        👍 Use `std::vector<char>` instead.
        ```C++
        std::vector<char> v = {true, false, true};
        char& ref = v[0];     // ✅ Works!
        char* ptr = &v[0];    // ✅ Works!
        ```
* C-style array:
    * ⚠️ Avoid using C-style array in most cases due to the loss of length information in C-style array decay.
* C-style string:
    * ⚠️ Avoid non-const C-style string objects. ✅ use `std::string`.
    * 👎️ Avoid C-style string symbolic constants. ✅ use `std::string_view`.


Just like function templates, class templates are typically defined in header files.










Is there any reason to use = default copy constructor? Yes, for two reasons:
1. It's generally better to be explicit than implicit.
2. Implicit behavior can change (e.g. if you add a move constructor or move assignment, the implicit copy constructor will no longer be generated, but an = default copy constructor still will be generated).







Inline functions are typically defined in "header" files, where they can be #included into the top of any code file 
   that needs to see the full definition of the identifier. This ensures that all inline definitions for an identifier are "identical".
   This is particularly useful for "header-only libraries" (no .cpp files are included).

Why not make all functions inline and defined in a header file?
- Mainly because doing so can increase your compile times significantly.
- Conversely, if you change the code in a .cpp file, only that .cpp file needs to be recompiled.
- If you change any of the code in the header, then you’ll need to recompile every file that includes that header.