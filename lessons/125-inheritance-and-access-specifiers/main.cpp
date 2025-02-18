/* Access specifiers
*/

class Base
{
public:
    int m_public {}; // can be accessed by anybody
protected:
    int m_protected {}; // can be accessed by Base members, friends, and derived classes
private:
    int m_private {}; // can only be accessed by Base members and friends (but not derived classes)
};

class Derived1: public Base
{
public:
    Derived1()
    {
        m_public = 1; // allowed: can access public base members from derived class
        m_protected = 2; // allowed: can access protected base members from derived class
        m_private = 3; // not allowed: can not access private base members from derived class
    }
};

void func1()
{
    Base base;
    base.m_public = 1; // allowed: can access public members from outside class
    base.m_protected = 2; // not allowed: can not access protected members from outside class
    base.m_private = 3; // not allowed: can not access private members from outside class

}


/* Different kinds of inheritance

- If you do not choose an inheritance type, C++ defaults to private inheritance 
  (just like members default to private access if you do not specify otherwise).

- When members are inherited, the access specifier for an inherited member may be changed 
  depending on the type of inheritance used:

                                Kind of inheritance
  Access specifier  
                    | Public       | Protected    | Private
  Public            | Public       | Protected    | Private
  Protected         | Protected    | Protected    | Private
  Private           | Inaccessible | Inaccessible | Inaccessible            
*/

// Inherit from Base publicly
class Pub: public Base
{
};

// Inherit from Base protectedly
class Pro: protected Base
{
};

// Inherit from Base privately
class Pri: private Base
{
};

class Def: Base // Defaults to private inheritance
{
};


int main()
{
    // Access specifiers
    func1();

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/inheritance-and-access-specifiers/
*/