/*
- std::cout is actually an object of type std::ostream.
- std::cin is an object of type std::istream.
*/


#include <iostream>

class Point
{
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Point(double x=0.0, double y=0.0, double z=0.0)
      : m_x{x}, m_y{y}, m_z{z}
    {
    }

    friend std::ostream& operator<< (std::ostream& out, const Point& point);
    friend std::istream& operator>> (std::istream& out, Point& point);
};

std::ostream& operator<< (std::ostream& out, const Point& point)
{
    out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')'; // actual output done here

    return out;
}

std::istream& operator>> (std::istream& in, Point& point)
{
    double x{};
    double y{};
    double z{};

    in >> x >> y >> z;      // will run into failure mode if any of the input is not a double

    // In case a value is extractable but semantically invalid, we might need to manually put the stream in a failure mode
    // so that the caller of this function can then check std::cin to see if it failed and handle that case as appropriate.
    if (x < 0.0 || y < 0.0 || z < 0.0)       // assume that negative values are invalid
        in.setstate(std::ios_base::failbit);

    point = in ? Point{x, y, z} : Point{};    // if extraction fails, then reset the point to default state

    return in;
}

int main()
{
    const Point point1 { 2.0, 3.0, 4.0 };

    std::cout << point1 << '\n';

    return 0;
}


/* References

- https://www.learncpp.com/cpp-tutorial/overloading-the-io-operators/
*/