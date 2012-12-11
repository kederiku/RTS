#include <point.h>
#include <iostream>

Point::Point(void): x(0), y(0)
{
}

Point::Point(const unsigned short int& x, const unsigned short int& y): x(x), y(y)
{
}

Point::Point(const unsigned short int& i): x(i), y(i)
{
}

Point::Point(const Point& right)
{
	this->x = right.x;
	this->y = right.y;
}

Point&
Point::operator=(const Point& right)
{
	this->x = right.x;
	this->y = right.y;
	return *this;
}

Point&
Point::operator+=(const Point& right)
{
	this->x += right.x;
	this->y += right.y;
	return *this;
}

Point&
Point::operator-=(const Point& right)
{
	this->x -= right.x;
	this->y -= right.y;
	return *this;
}

Point
Point::operator+(const Point& right) const
{
	Point	ret(*this);

	ret.x += right.x;
	ret.y += right.y;
	return ret;
}

Point
Point::operator-(const Point& right) const
{
	Point	ret(*this);

	ret.x -= right.x;
	ret.y -= right.y;
	return ret;
}

bool
Point::operator!=(const Point& right) const
{
	return this->x != right.x || this->y != right.y;
}

bool
Point::operator==(const Point& right) const
{
	return this->x == right.x && this->y == right.y;
}

Point&
Point::operator=(const unsigned short int& i)
{
	this->x = i;
	this->y = i;
	return *this;
}

bool
Point::operator!=(const unsigned short int& i) const
{
	return this->x != i || this->y != i;
}

bool
Point::operator==(const unsigned short int& i) const
{
	return this->x == i && this->y == i;
}

bool
Point::operator>(const unsigned short int& i) const
{
	return this->x > i && this->y > i;
}

bool
Point::operator<(const unsigned short int& i) const
{
	return this->x < i && this->y < i;
}

void
Point::print(void) const
{
	std::cout << "x\t" << this->x << "\ty\t" << this->y << std::endl;
}
