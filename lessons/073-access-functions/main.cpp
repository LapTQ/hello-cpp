/*

- Getters are usually made const, so they can be called on both const and non-const objects. 
- Setters should be non-const, so they can modify the data members.
*/


#include <iostream>

class Date
{
private:
    int m_year { 2020 };
    int m_month { 10 };
    int m_day { 14 };

public:
    void print()
    {
        std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
    }

    int getYear() const { return m_year; }        // getter for year
    void setYear(int year) { m_year = year; }     // setter for year
};

/* - Getters should return by value or by const lvalue reference

- But attention: The return type should match the data member’s type.
  In the below example: m_name is of type std::string, so getName() returns const std::string&.
  Returning a std::string_view would require a temporary std::string_view to be created and returned every time the function was called.
  That’s needlessly inefficient.

  => For getters, using auto is a useful way to ensure that no conversions occur, but it might not be as clear to the reader.
     So we’ll generally prefer explicit return types for getters.
*/

#include <string>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	
    const std::string& getName() const { return m_name; } //  getter returns by const reference
    const auto& getName2() const { return m_name; } //  getter returns by const reference, using auto to ensure that no conversions occur
};


/* Do not return non-const references to private data members

- Because it will provide direct access to that member even if the member is private.
*/


int main()
{
    Date d{};
    d.setYear(2021);
    std::cout << "The year is: " << d.getYear() << '\n';


    // Getters should return by value or by const lvalue reference
    Employee joe{}; // joe exists until end of function
	joe.setName("Joe");
	std::cout << joe.getName(); // returns joe.m_name by reference
    std::cout << joe.getName2(); // returns joe.m_name by reference

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/access-functions/
- https://www.learncpp.com/cpp-tutorial/member-functions-returning-references-to-data-members/
*/