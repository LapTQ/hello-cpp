
/* Multiple inheritance
*/

class Dad
{
private:
    int m_dad;

public:
    Dad(int dad)
        : m_dad { dad }
    {
    }
};

class Mom
{
private:
    int m_mom;

public:
    Mom(int mom)
        : m_mom { mom }
    {
    }
};


class Child: public Dad, public Mom
{
private:
    int m_child;

public:
    Child(int dad, int mom, int child)
        : Dad { dad }, Mom { mom }, m_child { child }
    {
    }
};


/* Mixin

- ... is a small class that can be inherited from in order to add properties to a class.

- In the following example, we use explicit Box::, Label::, and Tooltip:: scope resolution prefixes because:
    + disambiguate function call for multiple inheritance. For example: Label::setText() and Tooltip::setText()
    + make our code easier to understand.

- Because mixins are designed to add functionality to the derived class, not to provide an interface, mixins typically do not use virtual functions.
- Instead, if a mixin class needs to be customized to work in a particular way, templates are typically used.
*/

// h/t to reader Waldo for this example
#include <string>
#include <string_view>

struct Point2D
{
	int x{};
	int y{};
};

class Box // mixin Box class
{
public:
	void setTopLeft(Point2D point) { m_topLeft = point; }
	void setBottomRight(Point2D point) { m_bottomRight = point; }
private:
	Point2D m_topLeft{};
	Point2D m_bottomRight{};
};

class Label // mixin Label class
{
public:
	void setText(const std::string_view str) { m_text = str; }
	void setFontSize(int fontSize) { m_fontSize = fontSize; }
private:
	std::string m_text{};
	int m_fontSize{};
};

class Tooltip // mixin Tooltip class
{
public:
	void setText(const std::string_view str) { m_text = str; }
private:
	std::string m_text{};
};

class Button : public Box, public Label, public Tooltip {}; // Button using three mixins

void func2()
{
	Button button{};
	button.Box::setTopLeft({ 1, 1 });
	button.Box::setBottomRight({ 10, 10 });
	button.Label::setText("Submit");
	button.Label::setFontSize(6);
	button.Tooltip::setText("Submit the form to the server");
}


int main()
{
}


/* References

- https://www.learncpp.com/cpp-tutorial/multiple-inheritance/
*/