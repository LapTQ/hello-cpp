

## Initializations

```C++
int a;         // default-initialization (no initializer)
int b = 5;     // copy-initialization
int c ( 6 );   // direct-initialization

int f {};      // value-initialization/zero-initialization
int d { 7 };   // direct-list initialization
```


## Clear the input buffer

```C++
std::cin.ignore(100, '\n');  // clear up to 100 characters out of the buffer, or until a '\n'
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore all characters up to the next ‘\n’
```

## Check if there is extraneous input

```C++
std::cout << (!std::cin.eof() && std::cin.peek() != '\n') << "\n";
```

* The `std::cin.eof()` function returns true if the last input operation reached the end of the input stream.
* The `std::cin.peek()` function returns the next character in the input sequence, without extracting it.


## Handle failed extractions or overflow of a numeric type

```C++
if (std::cin.fail()) // equivalent to if (!std::cin)
{
    if (std::cin.eof()) // If the user entered an EOF
    {
        std::exit(0); // Shut down the program now
    }

    std::cin.clear(); // Put us back in 'normal' operation mode
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');     // And remove the bad input
}
```


## If your program runs but the console window flashes and closes immediately

```C++
std::cin.clear(); // reset any error flags
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any characters in the input buffer until we find a newline
std::cin.get(); // get one more char from the user (waits for user to press enter)
```


## Initialize string

```C++
std::string name {}; // empty string
std::string name2 { "Alex" }; // initialize name with C-style string literal "Alex"
name2 = "Johnnnn";               // change name using C-style string literal
```


## Extract a line of text from input stream, including whitespace

```C++
std::getline(std::cin >> std::ws, name); // read a full line of text into name
// The std::ws input manipulator tells std::cin to ignore any leading whitespace
// (spaces, tabs, newlines) at the start of the string.
// This needs to be done for each std::getline() call, as std::ws is not preserved across calls.
```


## Namespaces alias

```C++
namespace Active = Foo::Goo;
```


# Switch case

```C++
switch (2)
{
case 1: // Does not match
    std::cout << 1 << '\n'; // Skipped
case 2: // Match!
    std::cout << 2 << '\n'; // Execution begins here
    [[fallthrough]]; // intentional fallthrough -- note the semicolon to indicate the null 
case 3:
    std::cout << 3 << '\n'; // This is also executed
    [[fallthrough]]; // intentional fallthrough -- note the semicolon to indicate the null 
default:
    std::cout << 5 << '\n'; // This is also executed
}
```

* without a `break` or `return`, execution will overflow into subsequent cases.
* The [[fallthrough]] attribute is used to tell the compiler that the fallthrough is intended.


## `for` loop

```C++
int i{ 0 };
for ( ; i < 10; ) // no init-statement or end-expression
{
    std::cout << i << ' ';
    ++i;
}
```

```C++
for ( ; ; ) // infinite loop
{
    std::cout << "Enter 'q' to quit: ";
    char c{};
    std::cin >> c;

    if (c == 'q')
        break;
} // equivalent to while (true)
```

```C++
for (int x{ 0 }, y{ 9 }; x < 10; ++x, --y)  // multiple counters
    std::cout << x << ' ' << y << '\n';
```


## Exit

```C++
void cleanup()
{
    // code here to do any kind of cleanup required
    std::cout << "cleanup!\n";
}

int main()
{
    // register cleanup() to be called automatically when std::exit() is called
    std::atexit(cleanup);

    return 0;
}
```

* The function being registered must take no parameters and have no return value.
* You can register multiple cleanup functions, and they will be called in the reverse order they were registered.


## Pseudo-random number generation

Please go to the lesson.


## Type aliases and typedef

```C++
using score_t = int; // type alias
typedef int score_t;  // typedef
```

* Prefer type aliases over typedefs. typedef is an older way of creating an alias for a type.
* They do not actually define a new, distinct type.


## Get type

```C++
#include <type_traits> // note: decltype(x) evaluates to the type of x
auto add(int x, double y) -> std::common_type_t<decltype(x), decltype(y)>;
```

```C++
std::cout << typeid(i).name() << '\n'; // show us the name of the type for i
```


## Delete function

```C++
void printInt(bool) = delete; // calls to this function will halt compilation
```

Deleting all non-matching overloads:
```C++
void printInt(int x) // This function will take precedence for arguments of type int

template <typename T>
void printInt(T x) = delete; // This function will take precedence for all other types
```


## Function templates

Template argument deduction:
```C++
template <typename T>
void print(T x) { std::cout << x; }

void print(bool x) { std::cout << std::boolalpha << x; }
```

* To consider only template function overloads (with the empty angled brackets):
    ```C++
    print<>(true); // deduces print<bool>(bool) (prints 1): non-template functions not considered
    ```
* To consider all overloads:
    ```C++
    print(true); // deduces print(bool) (prints true): consider both template and non-template functions, but non-template functions take precedence
    ```

We can disallow certain types from being used with a function template by using the `delete` specifier:
```C++
template <typename T>
T addOne(T x)
{
    return x + 1;
}

template <>
const char* addOne(const char* x) = delete;
// addOne("Hello, world!"); // compile error
```

Non-type template parameters:
```C++
template <double D> // requires C++20 for floating point non-type parameters
double getSqrt2()
{
    static_assert(D >= 0.0);

    if constexpr (D >= 0)
        return std::sqrt(D);

    return 0.0;
}

template <auto N>   // type deduction for non-type template parameters
void print2()
{
    std::cout << N << '\n';
}
```


## Lvalue reference to const

```C++
const int x3 { 5 };
const int& ref_x3 { x3 };

int y3 { 6 };  // modifiable lvalue
const int& ref_y3 { y3 };
```

An lvalue reference to const can be initialized with an rvalue:
```C++
const int& ref_rvalue { 5 }; // okay
```

## Pointers

```C++
int x{ 5 };
    
int* ptr; // an uninitialized pointer (holds a garbage address)
int* ptr2{};     // a null pointer (we'll discuss these in the next lesson)
int* ptr3{ &x }; // a pointer initialized with the address of variable x
// the address-of operator (&) returns a pointer
```

Checking for null pointers:
```C++
if (ptr == nullptr) // explicit test for equivalence
    std::cout << "ptr is null\n";
else
    std::cout << "ptr is non-null\n";
```

Create a **pointer to const**:
```C++
const int* ptr { ... }; // const keyword before the data type
```

Create a **const pointer**:
```C++
int* const ptr { ... }; // const keyword after the data type
```

Create a **const pointer to a const**:
```C++
const int* const ptr { ... }; // const keyword before and after the data type
```


## std::optional

* `std::optional` is a class template type that implements an optional value. That is, a `std::optional<T>` can either have a value of type `T`, or not.

```C++
#include <optional> // for std::optional (C++17)

std::optional<int> doIntDivision2(int x, int y)
{
    if (y == 0)
        return {}; // or return std::nullopt
    return x / y;
}

int main()
{
    std::optional<int> result1 { doIntDivision2(20, 5) };
    if (result1) // if the function returned a value
        std::cout << "Result 1: " << *result1 << '\n';
    else
        std::cout << "Result 1: failed\n";

    
    // use std::optional is easy
    std::optional<int> o1 { 5 };            // initialize with a value
    std::optional<int> o2 {};               // initialize with no value
    std::optional<int> o3 { std::nullopt }; // initialize with no value

    // check if the optional has a value
    if (o1.has_value()); // call has_value() to check if o1 has a value
    if (o2);        // use implicit conversion to bool

    // get the value
    std::cout << *o1;             // dereference (undefined behavior if o1 does not have a value)
    std::cout << o2.value();      // throws std::bad_optional_access exception if o2 does not have a value
    std::cout << o3.value_or(42); //  value `42` if o3 doesn't have a value

    return 0;
}
```


## Class template

Reminder: A “class type” is a struct, class, or union type. Although we’ll be demonstrating “class templates” on structs for simplicity, everything here applies equally well to classes.

```C++
template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};


template <typename T, typename U>
constexpr auto max(Pair<T, U> p) 
{
    return (p.first < p.second ? p.second : p.first);
}

void func1()
{
    Pair<int, int> p1{ 5, 6 };        // instantiates Pair<int> and creates object p1
    std::cout << p1.first << ' ' << p1.second << '\n';

    Pair<double, double> p2{ 1.2, 3.4 }; // instantiates Pair<double> and creates object p2
    std::cout << p2.first << ' ' << p2.second << '\n';

    std::cout << max<int>(p1) << " is larger\n"; // explicit call to max<int>
    std::cout << max(p2) << " is larger\n";      // call to max<double> using template argument deduction
}
```

Type deduction guide (only needed in C++17):
```C++
// deduction guide for our Pair (needed in C++17 only)
template <typename T, typename U>
Pair(T, U) -> Pair<T, U>; // should deduce to Pair<T, U>

void func3()
{
    Pair<int, int> p1{ 1, 2 }; // ok    
    Pair p4{ 1, 2 };  // compile error in C++17 (okay in C++20) without deduction guide
}
```

Type template parameters with default values:
```C++

template <typename T=int, typename U=int> // default T and U to type int
struct Pair2
{
    T first{};
    U second{};
};

template <typename T, typename U>
Pair2(T, U) -> Pair2<T, U>;

void func4()
{
    Pair2 p5; // use default Pair2<int, int>
}
```


## Const member function

```C++
struct Date2
{
    int year {};
    int month {};
    int day {};

    void print() const // const member function
    {
        std::cout << year << '/' << month << '/' << day << '\n';
    }
};

void func4()
{
    const Date2 date3 { 2020, 10, 14 };
    date3.print(); // okay
}
```

It is possible to overload a member function to have a const and non-const version of the same function. This works because the const qualifier is considered part of the 
  function’s signature.
```C++
struct Something
{
    void print()
    {
        std::cout << "non-const\n";
    }

    void print() const
    {
        std::cout << "const\n";
    }
};

void func5()
{
    Something s1{};
    s1.print(); // calls print()

    const Something s2{};
    s2.print(); // calls print() const
}
```


## Constructors

Deligating constructors:
```C++
class Employee
{
private:
    std::string m_name { "???" };
    int m_id { 0 };

public:
Employee(std::string_view name)
        : Employee{ name, 0 } // delegate initialization to Employee(std::string_view, int) constructor
    {
    }
    
    Employee(std::string_view name, int id)
    : m_name{ name }, m_id { id }
    {
        std::cout << "Employee " << m_name << " created\n";
    }
};

void func8()
{
    Employee e1{ "James" };
    Employee e2{ "Dave", 42 };
}
```

Using `= default` to generate a default copy constructor
```C++
class Fraction3
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction3(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    // Explicitly request default copy constructor
    Fraction3(const Fraction3& fraction) = default;
};
```

Using `= delete` to prevent copy constructor
```C++
class Fraction4
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction4(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    // Prevent copy constructor
    Fraction4(const Fraction4& fraction) = delete;
};
```

Using `explicit` to prevent implicit conversions:
```C++
class Dollars2
{
private:
    int m_dollars{};

public:
    explicit Dollars2(int d) // now explicit
        : m_dollars{ d }
    {
    }

    int getDollars() const { return m_dollars; }
};

void print2(Dollars2 d)
{
    std::cout << "$" << d.getDollars();
}

void func3()
{
    print(5); // prints $5
    print2(5); // compile error: cannot convert int to Dollars2
    print2(static_cast<Dollars2>(5)); // okay, explicit conversion
}
```

Constexpr constructors:
```C++
class Pair2 // Pair is no longer an aggregate
{
private:
    int m_x {};
    int m_y {};

public:
    Pair2(int x, int y): m_x { x }, m_y { y } {}
};

class Pair3
{
private:
    int m_x {};
    int m_y {};

public:
    constexpr Pair3(int x, int y): m_x { x }, m_y { y } {} // now constexpr
};

void func2()
{
    constexpr Pair2 p2 { 5, 6 };       // compile error: p2 is not a literal type
    constexpr Pair3 p3 { 5, 6 };       // okay, p3 is a literal type
}
```


## Constexpr functions that return const references (or pointers)

Let's see a member function:
```C++
constexpr const int* const getXPtr() const { return &m_x; }
```

That’s a lot of const-ing!
* The constexpr indicates that the member function can be evaluated at compile-time. 
* The 1st and 2nd const indicates a const pointer to const.
* The 3rd const means the member-function itself is const so it can be called on const objects.


## Nested types (member types)

```C++
class Fruit
{
public:
	// Nested type
	enum Type
	{
		apple,
		banana,
		cherry
	};

private:
	Type m_type {};
	int m_percentageEaten { 0 };

public:
	Fruit(Type type) :
		m_type { type }
	{
	}

	// ...

	bool isCherry() { return m_type == cherry; }  // access without scope resolution operator ::
};
```

Nested types can be typedefs or type aliases:
```C++
class Employee
{
public:
    using IDType = int;

private:
    std::string m_name{};
    IDType m_id{};
    double m_wage{};

// ...
}
```

## Destructor

```C++
class Simple
{
private:
    int m_id {};

public:
    Simple(int id)
        : m_id { id }
    {
        std::cout << "Constructing Simple " << m_id << '\n';
    }

    ~Simple() // here's our destructor
    {
        std::cout << "Destructing Simple " << m_id << '\n';
    }

    int getID() const { return m_id; }
};

int main()
{
    // Allocate a Simple
    Simple simple1{ 1 };
    {
        Simple simple2{ 2 };
    } // simple2 dies here

    return 0;
} // simple1 dies here
```


## Static member functions

Static member functions can also be defined outside of the class declaration. This works the same way as for normal member functions.

```C++
class IDGenerator
{
private:
    static inline int s_nextID { 1 };

public:
     static int getNextID(); // Here's the declaration for a static function
};

// Here's the definition of the static function outside of the class.  Note we don't use the static keyword here.
int IDGenerator::getNextID() { return s_nextID++; }
```


## Friend

Friend non-member functions:
```C++
class Accumulator
{
private:
    int m_value { 0 };

public:
    void add(int value) { m_value += value; }

    // friend declaration
    friend void print(const Accumulator& accumulator);
};

// friend definition outside of the class
void print(const Accumulator& accumulator)
{
    // it can access the private members of Accumulator
    std::cout << accumulator.m_value;
}


class Accumulator2
{
private:
    int m_value { 0 };

public:
    void add(int value) { m_value += value; }

    // friend function defined inside the class
    // is treated as a non-member function... that's why I have to choose a name different from print
    friend void print2(const Accumulator2& accumulator)
    {
        std::cout << accumulator.m_value;
    }
};
```

Multiple friends:
```C++
class Humidity; // forward declaration of Humidity

class Temperature
{
private:
    int m_temp { 0 };
public:
    explicit Temperature(int temp) : m_temp { temp } { }

    friend void printWeather(const Temperature& temperature, const Humidity& humidity); // forward declaration needed for this line
};

class Humidity
{
private:
    int m_humidity { 0 };
public:
    explicit Humidity(int humidity) : m_humidity { humidity } {  }

    friend void printWeather(const Temperature& temperature, const Humidity& humidity);
};

void printWeather(const Temperature& temperature, const Humidity& humidity)
{
    std::cout << "The temperature is " << temperature.m_temp <<
       " and the humidity is " << humidity.m_humidity << '\n';
}
```

Friend classes:
```C++
class Storage
{
private:
    int m_nValue {};
public:
    Storage(int nValue)
       : m_nValue { nValue }
    { }

    // Make the Display class a friend of Storage
    friend class Display;
};

class Display
{

public:
    // Because Display is a friend of Storage, Display members can access the private members of Storage
    void displayStorage(const Storage& storage)
    {
        std::cout << storage.m_nValue << '\n';
    }
};
```

Friend member functions:
* Instead of making an entire class a friend, you can make a single member function a friend.
* However, the process might be more complicated than you think:
    * Storage needs to seen the full definition of class Display => define Display before Storage.
    * Storage needs to be forward declaration before use in Display => forward declare Storage before Display.
    * Friend member functions needs to see the full definition of Storage to access its private members => define displayStorage outside of Display and after Storage.
```C++
class Storage2; // forward declaration for class Storage

class Display2
{
public:
	void displayStorage(const Storage2& storage);
};

class Storage2 // full definition of Storage class
{
private:
	int m_nValue {};
public:
	Storage2(int nValue, double dValue)
		: m_nValue { nValue }
	{
	}

	friend void Display2::displayStorage(const Storage2& storage);
};

// Requires seeing the full definition of class Storage (as we access Storage members)
void Display2::displayStorage(const Storage2& storage)
{
    std::cout << storage.m_nValue << '\n';
}
```

## `std::vector`

`std::vector` is defined in the `<vector>` header as a class template:
```C++
// Value initialization
std::vector<int> empty{}; // vector containing 0 int elements, default constructor
```

Constructing a std::vector of a specific length:
* use direct initialization (braced initialization), instead of list initialization (with initializer list)
```C++
std::vector<int> v1 = 10;     // copy initialization, but compile error because 10 won't match explicit constructor
std::vector<int> v2(10);      // 10 not an initializer list => won't match list constructor, so it matches `explicit std::vector<T>(std::size_t)` constructor
std::vector<int> v3{ 10 };    // { 10 } interpreted as initializer list, matches list constructor
std::vector<int> v4 = { 10 }; // copy, { 10 } interpreted as initializer list, matches list constructor
std::vector<int> v5({ 10 });  // same as v4, but it's copy construction, not direct initialization
std::vector<int> v6 {};       // {} is empty initializer list, matches default constructor
std::vector<int> v7 = {};     // {} is empty initializer list, matches default constructor
```

Accessing array elements using the subscript operator (operator[]):
```C++
std::vector<int> primes{ 2, 3, 5, 7 }; 
std::cout << primes[0] << '\n'; // 2
```

To get the length of a `std::vector`:
* use the `.size()` member function or the `std::size()` function (C++17).
* C++20 in introduces the `std::ssize()` non-member function, which returns the length as a large "signed" integral type (usually std::ptrdiff_t).
```C++
std::vector<int> primes{ 2, 3, 5, 7 };
  
// get the length of a std::vector
std::cout << "The length of primes is: " << primes.size() << '\n'; // using .size() member function, returns length as type `size_type` (alias for `std::size_t`)
std::cout << "The length of primes is: " << std::size(primes) << '\n'; // (C++17) using std::size() function
int length { static_cast<int>(primes.size()) }; // static_cast to avoid signed/unsigned conversion warning or error

std::cout << "length: " << std::ssize(primes); // C++20, returns the length as a large "signed" integral type
int length2 { static_cast<int>(std::ssize(primes)) }; // static_cast return value to int

std::size_t length3 { primes.size() }; // okay, no conversion required
```

Passing a `std::vector`:
```C++
void passByRef(const std::vector<int>& arr) // we must explicitly specify <int> here
{
    // ...
}

template <typename T>       // use a template
void passByRef2(const std::vector<T>& arr)
{
    // ...
}

void passByRef3(const auto& arr) // (C++20) can be desirable when we might want to operate on more than just a std::vector
{
    // ...
}
```

Use signed integral type for index:
* Use a conversion function with a short name:
    ```C++
    template <typename T>
    constexpr std::size_t toUZ(T value)
    {
        // make sure T is an integral type
        static_assert(std::is_integral<T>() || std::is_enum<T>());

        return static_cast<std::size_t>(value);
    }

    template <typename T>
    void printReverse5(const std::vector<T>& arr)
    {
        auto length { static_cast<Index>(arr.size()) };
        for (auto index{ length - 1 }; index >= 0; --index) // index is signed
        {
            std::cout << arr[toUZ(index)] << ' ';
        }

        std::cout << '\n';
    }
* Use a custom view by overloading operator[]:
    `SignedArrayView.h`:
    ```C++
    #ifndef SIGNED_ARRAY_VIEW_H
    #define SIGNED_ARRAY_VIEW_H

    #include <cstddef> // for std::size_t and std::ptrdiff_t

    template <typename T>
    class SignedArrayView // requires C++17
    {
    private:
        T& m_array;

    public:
        using Index = std::ptrdiff_t;

        SignedArrayView(T& array)
            : m_array{ array } {}

        // Overload operator[] to take a signed index
        constexpr auto& operator[](Index index) { return m_array[static_cast<typename T::size_type>(index)]; }
        constexpr const auto& operator[](Index index) const { return m_array[static_cast<typename T::size_type>(index)]; }
        constexpr auto ssize() const { return static_cast<Index>(m_array.size()); }
    };

    #endif
    ```

    `main.cpp`:
    ```C++
    #include "SignedArrayView.h"

    template <typename T>
    void printReverse6(const std::vector<T>& arr)
    {
        SignedArrayView sarr{ arr };
        auto length { sarr.ssize() };
        for (auto index{ length - 1 }; index >= 0; --index) // index is signed
        {
            std::cout << sarr[index] << ' ';
        }
    }
Notes about `typename`:
    * Any name that depends on a type containing a template parameter is called a dependent name. Dependent names must be prefixed with the keyword `typename` in order to be used as a type.
    * In the above example, `T` is a type with a template parameter, so nested type `T::size_type` is a dependent name, and must be prefixed with `typename` to be used as a type.

Resizing a `std::vector` at runtime:
```C++
#include <iostream>
#include <vector>

template <typename T>
void resizeBigger() {
    std::vector v{ 0, 1, 2 }; // create vector with 3 elements
    std::cout << "The length is: " << v.size() << '\n';

    v.resize(5);              // resize to 5 elements
    std::cout << "The length is: " << v.size() << '\n';

    for (auto i : v)
        std::cout << i << ' ';

    std::cout << '\n';
}

template <typename T>
void resizeSmaller() {
    std::vector v{ 0, 1, 2, 3, 4 };
    std::cout << "The length is: " << v.size() << '\n';

    v.resize(3);
    std::cout << "The length is: " << v.size() << '\n';

    for (auto i : v)
        std::cout << i << ' ';

    std::cout << '\n';
}

void func1()
{
    // Resize a std::vector at runtime
    resizeBigger<int>();   // 0 1 2 0 0
    resizeSmaller<int>();  // 0 1 2
}
```
`std::vector` has a member function called `shrink_to_fit()` that requests that the vector shrink its capacity to match its length. Note that This request is non-binding, meaning the implementation is free to ignore it.
```C++
void func3()
{ 
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    v.shrink_to_fit();
    std::cout << "The length is: " << v.size() << '\n';     // 3
    std::cout << "The capacity is: " << v.capacity() << '\n'; // 3

}
```