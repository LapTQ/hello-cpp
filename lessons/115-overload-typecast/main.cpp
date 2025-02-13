#include <iostream>

class Cents
{
private:
    int m_cents{};
public:
    Cents(int cents=0)
        : m_cents{ cents }
    {
    }

    // Overloaded int cast
    operator int() const { return m_cents; }

    int getCents() const { return m_cents; }
    void setCents(int cents) { m_cents = cents; }
};

class Dollars
{
private:
    int m_dollars{};
public:
    Dollars(int dollars=0)
        : m_dollars{ dollars }
    {
    }

    // Allow us to convert Dollars into Cents
    operator Cents() const { return Cents{ m_dollars * 100 }; }
};

void printCents(Cents cents)
{
    std::cout << cents.getCents() << " cents\n";
}


/*  Explicit typecasts

Just like we can make constructors explicit so that they can’t be used for implicit conversions, we can also make our overloaded typecasts explicit for the same reason.
*/

class Dollars2
{
private:
    int m_dollars{};
public:
    Dollars2(int dollars=0)
        : m_dollars{ dollars }
    {
    }
     // now explicit
    explicit operator Cents() const { return Cents{ m_dollars * 100 }; }
};


int main()
{
    Cents cents{ 7 };
    std::cout << static_cast<int>(cents) << " cents\n";

    Dollars dollars{ 9 };
    printCents(dollars);


    // Explicit typecasts
    Dollars2 dollars2{ 9 };
    printCents(dollars2); // error: no matching function for call to 'printCents'
    printCents(static_cast<Cents>(dollars2)); // 900 cents

    return 0;
}


/* Converting constructors vs overloaded typecasts

- Overloaded typecasts and converting constructors perform similar roles
- In general, a converting constructor should be preferred, as it allows the type being constructed to own the construction.
- There are a few cases where an overloaded typecast should be used instead:
    + When providing a conversion to a fundamental type or a type you can’t add members to (since you can’t define constructors for these types).
    + When avoiding circular dependencies.
*/

/* References

- https://www.learncpp.com/cpp-tutorial/overloading-typecasts/
*/