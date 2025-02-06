/* friend declaration

- a friend is a class or function (member or non-member) that has been granted 
  full access to the private and protected members of another class.
*/


/* Friend non-member functions

- In the below example, Note that because print() is a non-member function 
  (and thus does not have an implicit object), we must explicitly pass an Accumulator 
  object to print() to work with.
*/


#include <iostream>

class Accumulator
{
private:
    int m_value { 0 };

public:
    void add(int value) { m_value += value; }

    // Here is the friend declaration that makes non-member function void print(const Accumulator& accumulator) a friend of Accumulator
    friend void print(const Accumulator& accumulator);
};

void print(const Accumulator& accumulator)
{
    // it can access the private members of Accumulator
    std::cout << accumulator.m_value;
}


/* A friend non-member function defined inside a class is treated as a non-member function

- In the below example, print() is defined inside Accumulator, but it is not a member of Accumulator.
*/

class Accumulator2
{
private:
    int m_value { 0 };

public:
    void add(int value) { m_value += value; }

    // non-member functions... that's why I have to choose a name different from print
    friend void print2(const Accumulator2& accumulator)
    {
        std::cout << accumulator.m_value;
    }
};


/* Multiple friends
*/

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


/* Friend classes

Nots:
- Display is a friend of Storage does not mean Storage is also a friend of Display.
- Nor is friendship inherited. If class A makes B a friend, classes derived from B are not friends of A.
- A friend class declaration acts as a forward declaration for the class being friended. 
  This means we do not need to forward declare the class being friended before friending it.
*/

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


/* Friend member functions

- Instead of making an entire class a friend, you can make a single member function a friend.

- However, the process might be more complicated than you think:
  + Storage needs to seen the full definition of class Display => define Display before Storage.
  + Storage needs to be forward declaration before use in Display => forward declare Storage before Display.
  + Friend member functions needs to see the full definition of Storage to access its private members => define displayStorage outside of Display and after Storage.

- Fortunately, this pain is only necessary because we’re trying to do everything in a single file.
   A better solution is to put each class definition in a separate header file, with the member function 
   definitions in corresponding .cpp files.
*/

#include <iostream>

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


int main()
{
    // friend non-member functions
    Accumulator acc{};
    acc.add(5);
    print(acc);

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/friend-non-member-functions/
- https://www.learncpp.com/cpp-tutorial/friend-classes-and-friend-member-functions/
*/