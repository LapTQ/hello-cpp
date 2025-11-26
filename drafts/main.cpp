class Base
{
public:
    virtual ~Base() = default;
};

class Derived: public Base
{

};

int main()
{
    Derived d {};
    Base& b { d };
    Derived d2 { dynamic_cast<Derived&>(b)};
}