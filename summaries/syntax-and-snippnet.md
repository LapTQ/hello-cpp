

## Initializations

```C++
int a;         // default-initialization (no initializer)
int b = 5;     // copy-initialization
int c ( 6 );   // direct-initialization

int f {};      // value-initialization
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