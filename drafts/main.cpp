#include <vector>
#include <iostream>


namespace Students
{
    enum Names
    {
        kenny, // 0
        kyle, // 1
        stan=-2, // 2
        butters, // 3
        cartman, // 4
        max_students // 5
    };
}

int main()
{
    std::vector testScores { 78, 94, 66, 77, 14 };

    // testScores[Students::stan] = 76; // we are now updating the test score belonging to stan
    std::cout << Students::stan << "\n";
    std::cout << typeid(Students::stan).name() << "\n";


    return 0;
}