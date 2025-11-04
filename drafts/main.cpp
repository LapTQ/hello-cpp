#include <iostream>
#include <array>
#include <functional> // for std::reference_wrapper

int main()
{
    int x { 1 };
    int y { 2 };
    // std::array<int&, 2> refarr { x, y }; // compile error: cannot define array of references

    int& ref1 { x };
    int& ref2 { y };
    std::array valarr { ref1, ref2 }; // ok, but this is actually a std::array<int, 2>, not an array of references
    valarr[0] = 10;
    std::cout << valarr[0] << " " << x << '\n'; // 10 1

    std::array<std::reference_wrapper<int>, 2> arr { x, y };
    arr[0].get() = 10;
    std::cout << arr[0] << " " << x << '\n'; // 10 10

    return 0;
}