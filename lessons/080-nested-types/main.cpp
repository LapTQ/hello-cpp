/* Nested types (member types)

- Besides data members and member functions, a class can also contain nested types.
*/


#include <iostream>

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

	Type getType() { return m_type;  }
	int getPercentageEaten() { return m_percentageEaten;  }

	bool isCherry() { return m_type == cherry; }  // access without scope resolution operator ::
};


/* Nested typedefs and type aliases

- Nested types can be typedefs or type aliases.
*/

class Employee
{
public:
    using IDType = int;

private:
    std::string m_name{};
    IDType m_id{};
    double m_wage{};

public:
    Employee(std::string_view name, IDType id, double wage)
        : m_name { name }
        , m_id { id }
        , m_wage { wage }
    {
    }

    const std::string& getName() { return m_name; }
    IDType getId() { return m_id; } // can use unqualified name within class
};


/* Nested classes

- a nested class does not have access to the this pointer of the outer (containing) class.
  but can access any private members of the outer class that are in scope.
*/

#include <string>
#include <string_view>

class Employee2
{
public:
    using IDType = int;

    class Printer
    {
    public:
        void print(const Employee2& e) const
        {
            // Printer can't access Employee's `this` pointer
            // but we can access private members e.m_name and e.m_id that are in scope
            std::cout << e.m_name << " has id: " << e.m_id << '\n';
        }
    };

private:
    std::string m_name{};
    IDType m_id{};
    double m_wage{};

public:
    Employee2(std::string_view name, IDType id, double wage)
        : m_name{ name }
        , m_id{ id }
        , m_wage{ wage }
    {
    }
};


int main()
{
    // Nested types
	Fruit apple { Fruit::apple };   // outside the class, need ::


    // Nested typedefs and type aliases
    Employee john { "John", 1, 45000 };
    Employee::IDType id { john.getId() };


    // Nested classes
    const Employee2 john2{ "John", 1, 45000 };
    const Employee2::Printer p{}; // instantiate an object of the inner class
    p.print(john2);

	return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/nested-types-member-types/
*/