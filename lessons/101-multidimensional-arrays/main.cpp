/* Multidimensional C-style arrays
*/


/* Multidimensional std::array

- There is no standard library multidimensional array class in C++.
*/


/* Making two-dimensional std::array easier using an alias templates
*/

#include <iostream>
#include <array> // for std::array

template <typename T, std::size_t Row, std::size_t Col>
using Array2d = std::array<std::array<T, Col>, Row>;


/* Getting the dimensional lengths of a two-dimensional array

- use colLength2() instead of colLength1().
*/

template <typename T, std::size_t Row, std::size_t Col>
constexpr int colLength1(const Array2d<T, Row, Col>& arr) // you can return std::size_t if you prefer
{
    return arr[0].size(); // undefined behavior if length of first dimension is zero!
}

template <typename T, std::size_t Row, std::size_t Col>
constexpr int colLength2(const Array2d<T, Row, Col>&) // you can return std::size_t if you prefer
{
    return Col; // avoid undefined behavior
}


/* Flatting a two-dimensional array
*/

#include <functional> // for std::reference_wrapper

template <typename T, std::size_t Row, std::size_t Col>
using ArrayFlat2d = std::array<T, Row * Col>;

template <typename T, std::size_t Row, std::size_t Col>
class ArrayView2d
{
private:
    std::reference_wrapper<ArrayFlat2d<T, Row, Col>> m_arr {};

public:
    ArrayView2d(ArrayFlat2d<T, Row, Col> &arr)
        : m_arr { arr }
    {}

    // Get element via single subscript (using operator[])
    T& operator[](int i) { return m_arr.get()[static_cast<std::size_t>(i)]; }
    const T& operator[](int i) const { return m_arr.get()[static_cast<std::size_t>(i)]; }

    // Get element via 2d subscript (using operator(), since operator[] doesn't support multiple dimensions prior to C++23)
    T& operator()(int row, int col) { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }
    const T& operator()(int row, int col) const { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }

    // in C++23, you can uncomment these since multidimensional operator[] is supported
    //    T& operator[](int row, int col) { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }
    //    const T& operator[](int row, int col) const { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }

    int rows() const { return static_cast<int>(Row); }
    int cols() const { return static_cast<int>(Col); }
    int length() const { return static_cast<int>(Row * Col); }
};


int main()
{
    // Multidimensional C-style arrays
    int a[3][5] {
    { 1, 2, 3, 4, 5 },     // row 0
    { 6, 7, 8, 9, 10 },    // row 1
    { 11, 12, 13, 14, 15 } // row 2
    };

    int b[3][5]
    {
    { 1, 2 },          // row 0 = 1, 2, 0, 0, 0
    { 6, 7, 8 },       // row 1 = 6, 7, 8, 0, 0
    { 11, 12, 13, 14 } // row 2 = 11, 12, 13, 14, 0
    };

    b[2][3] = 7;

    int c[2][3][4]; // 2 x (3 x 4 array of int)


    // Multidimensional std::array
    using Array2dint34 = std::array<std::array<int, 4>, 3>; // backward of 3x4
    Array2dint34 arr {
        {  // note double braces
            { 1, 2, 3, 4 },
            { 5, 6, 7, 8 },
            { 9, 10, 11, 12 }
        }
    };


    // Making two-dimensional std::array easier using an alias templates
    Array2d<int, 3, 4> arr2 {
        {
            { 1, 2, 3, 4 },
            { 5, 6, 7, 8 },
            { 9, 10, 11, 12 }
        }
    };


    // Flatting a two-dimensional array
    ArrayFlat2d<int, 3, 4> arrFlat {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12 
    };
    ArrayView2d<int, 3, 4> arrView { arrFlat };

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/multidimensional-c-style-arrays/
- https://www.learncpp.com/cpp-tutorial/multidimensional-stdarray/
*/