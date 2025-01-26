#ifndef ADD_H
#define ADD_H

namespace BasicMath
{
    // function add() is part of namespace BasicMath
    int add(int x, int y);
    /*
    - If the forward declaration for add() wasn’t placed inside namespace BasicMath, 
      the compiler would complain that it hadn’t seen a declaration for the call to BasicMath::add(4, 3).
    */
}

#endif