#include "add.h"

namespace BasicMath
{
    // define the function add() inside namespace BasicMath
    int add(int x, int y)
    {
        return x + y;
    }
    /*
    - If the definition of function add() wasn’t inside namespace BasicMath, 
      the linker would complain that it couldn’t find a matching definition 
      for the call to BasicMath::add(4, 3).
    */
}