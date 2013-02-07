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

Point&
Point::operator*=(const unsigned short int& i)
{
	this->x *= i;
	this->y *= i;
	return *this;
}

Point&
Point::operator/=(const unsigned short int& i)
{
	this->x /= i;
	this->y /= i;
	return *this;
}

Point
Point::operator*(const unsigned short int& i)
{
	Point	ret(this->x * i, this->y * i);

	return ret;
}

Point
Point::operator/(const unsigned short int& i)
{
	Point	ret(this->x / i, this->y / i);

	return ret;
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

bool
Point::operator<(const Point& right) const
{
	if (this->y < right.y)
		return true;
	else if (this->y == right.y && this->x < right.x)
		return true;
	return false;
}

bool
Point::operator>(const Point& right) const
{
	if (this->y > right.y)
		return true;
	else if (this->y == right.y && this->x > right.x)
		return true;
	return false;
}

bool
Point::operator<=(const Point& right) const
{
	if (this->y < right.y)
		return true;
	else if (this->y == right.y && this->x <= right.x)
		return true;
	return false;
}

bool
Point::operator>=(const Point& right) const
{
	if (this->y > right.y)
		return true;
	else if (this->y == right.y && this->x >= right.x)
		return true;
	return false;
}

bool	Point::is_next_to(const Point& right) const
{
	if ((this->x -1 == right.x || this->x == right.x || this->x + 1 == right.x) &&
	    (this->y -1 == right.y || this->y == right.y || this->y + 1 == right.y))
		return true;
	return false;
}
