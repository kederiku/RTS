#ifndef _MAP_H_
#define _MAP_H_

#include "point.h"
#include "enums.h"
#include "Lib2D.h"
#include <iostream>
#include <stdlib.h>
#include <list>

struct	Case_map;
struct	size;

struct	data_ressource
{
	Point		pos;
	Point		size;
	e_ressource	ressource;
	int		capacity;
	data_ressource&	operator=(const data_ressource& right)
	{
		this->pos = right.pos;
		this->size = right.size;
		this->ressource = right.ressource;
		this->capacity = right.capacity;
		return *this;
	}
};

struct	data_building
{
	Point		pos;
	Point		size;
	e_type		building;
	int		player;
	data_building&	operator=(const data_building& right)
	{
		this->pos = right.pos;
		this->size = right.size;
		this->building = right.building;
		this->player = right.player;
		return *this;
	}
};


class	Map
{
	unsigned short int	__size_case;
	unsigned short int	__width;
	unsigned short int	__height;
	unsigned short int	__nb_ressource;
	unsigned short int	__nb_building;
	struct	Case_map
	{
		Point			pos_image;
		bool			collision;
		bool			init;
		Case_map(void): collision(0), init(false)
		{
		}
	}*			__case;
	data_ressource*		__info_resource;
	data_building*		__info_building;
	bool	load_data(const char* data, unsigned short int width, unsigned short int height);
	bool	init_case_map(int fd, unsigned short int width, unsigned short int height);
	bool	init_ressource(int fd, unsigned short int size);
	bool	save_data(int fd, void* data, int size);
public:
	Map(void);
	~Map(void);

	unsigned short int	get_width(void) const;
	unsigned short int	get_height(void) const;
	unsigned short int	get_size_case(void) const;
	bool			load_file(const char* level);
	bool			save_file(const char*);
	bool			init(unsigned short int size_case, unsigned short int width, unsigned short int height);
	void			set_case(unsigned short int x, unsigned short int y, const Point& pos, bool colision);
	bool			is_case_valid(unsigned short int x, unsigned short int y) const;
	void			del_case(unsigned short int x, unsigned short int y);
	void			get_pos_img(const Point& search, Point* ret) const;
	bool			is_init(void) const;
	void			clear(void);
	bool			is_case_init(unsigned short int x, unsigned short y) const;
	bool			get_ressource(std::vector<data_ressource>& data, const Point& min, const Point& max) const;
	bool			add_ressource(const Point& pos, const Point& size, e_ressource ressource, unsigned short int capacity);
	bool			add_building(const Point& pos, const Point& size, e_type type, unsigned short int player);
};

#endif
