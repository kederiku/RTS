#ifndef _POINT_H_
#define _POINT_H_

struct	Point
{
	unsigned short int	x;
	unsigned short int	y;

	Point(void);
	Point(const unsigned short int& x, const unsigned short int& y);
	Point(const unsigned short int& i);
	Point(const Point& right);

	Point&	operator=(const Point& right);
	Point&	operator+=(const Point& right);
	Point&	operator-=(const Point& right);
	Point	operator+(const Point& right) const;
	Point	operator-(const Point& right) const;
	bool	operator!=(const Point& right) const;
	bool	operator==(const Point& right) const;
	Point&	operator=(const unsigned short int& i);
	Point&	operator*=(const unsigned short int& i);
	Point&	operator/=(const unsigned short int& i);
	Point	operator*(const unsigned short int& i);
	Point	operator/(const unsigned short int& i);
	bool	operator!=(const unsigned short int& i) const;
	bool	operator==(const unsigned short int& i) const;
	bool	operator<(const unsigned short int& i) const;
	bool	operator>(const unsigned short int& i) const;
	bool	operator<(const Point& right) const;
	bool	operator>(const Point& right) const;
	bool	operator<=(const Point& right) const;
	bool	operator>=(const Point& right) const;
	void	print(const char* debug = 0) const;
	bool	is_next_to(const Point& right) const;
};

#endif
