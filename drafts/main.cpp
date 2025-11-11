#include <iostream>

int main()
{
    int x{ 2 };
    int y{ 5 };

    auto f {
        [new_var{ x * y }]() mutable 
        { 
            new_var++;
            std::cout << new_var << '\n'; 
        }
    };
    
    f();    // print 11
    f();    // print 12
}