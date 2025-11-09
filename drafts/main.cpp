#include <iostream>
#include <array>
#include <functional> // for std::reference_wrapper

int main()
{

    char c{ 'Q' };
    std::cout << c << '\n'; // undefined behavior
}