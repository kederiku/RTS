#ifndef _MAP_H_
#define _MAP_H_

#include "control.h"
#include "point.h"
#include "enums.h"
#include "info_pos.h"
#include "control/rect.h"
#include "Lib2D.h"
#include <iostream>
#include <stdlib.h>
#include "case_map.h"
#include <list>

struct	info_pos;
struct	Case_map;
struct	size;
class	Ressources;

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

class	Building;
class	Unit;
class	Control;

class	Map
{
	unsigned short int	__size_case;
	unsigned short int	__width;
	unsigned short int	__height;
	unsigned short int	__nb_ressource;
	unsigned short int	__nb_player;
	Case_map*		__case;
	data_ressource*		__info_resource;
	Point*			__begin_pos;

	bool			load_data(const char* data, unsigned short int width, unsigned short int height);
	bool			init_case_map(int fd, unsigned short int width, unsigned short int height);
	bool			init_ressource(int fd, unsigned short int size);
	bool			save_data(int fd, void* data, int size);
	bool			check_position(const Point& pos, const Point& size, const Point& min, const Point& max) const;
	Case_map*		get_case(unsigned x, unsigned y);
	const Case_map*		get_const_case(unsigned x, unsigned y) const;
	bool			search_ressource(Point& test, unsigned x, unsigned y, unsigned max, e_ressource type) const;
	bool			search_ressource(unsigned  x, unsigned y, e_ressource type) const;
	bool			search_town_center(unsigned  x, unsigned y, int id_player) const;
	bool			search_town_center(Point& ret, unsigned x, unsigned y, unsigned max, int id_player) const;
	bool			search_pos_unit(Point& ret, unsigned x, unsigned y, unsigned max, Lib2D::Control* unit) const;
public:
	Map(void);
	~Map(void);

	unsigned short int	get_width(void) const;
	unsigned short int	get_height(void) const;
	unsigned short int	get_size_case(void) const;
	bool			load_file(const char* level);
	bool			save_file(const char*);
	bool			init(unsigned short int size_case, unsigned short int width, unsigned short int height);
	void			set_case(unsigned short int x, unsigned short int y, const Point& pos, bool collision);
	void			get_pos_img(const Point& search, Point* ret) const;
	bool			is_init(void) const;
	void			clear(void);
	bool			get_ressource(std::vector<data_ressource>& data) const;
	bool			add_ressource(const Point& pos, const Point& size, e_ressource ressource, unsigned short int capacity);
	void			add_building(Point pos, Building* building);
	bool			check_collision_construction(const Point& pos_build, Lib2D::Control* ctrl) const;
	bool			get_neighbor(const Point& pos, info_pos* neighbor, unsigned& size, Lib2D::Control* unit) const;
	int			get_distance(const Point& begin, const Point end) const;
	void			set_case_ressource(Point pos, Point size, Ressources* image);
	void			set_building(Building* building);
	bool			is_case_valid(unsigned  x, unsigned y) const;
	bool			is_case_valid(const Point& tab_pos, const Point& unit_pos, Lib2D::Control* unit) const;
	void			set_unit(unsigned  x, unsigned y, Unit* unit);
	Unit*			get_unit(unsigned  x, unsigned y, int id_player);
	bool			get_closest_ressource(const Point& begin, Point& ret, e_ressource type) const;
	bool			get_closest_towncenter(const Point& begin, Point& ret, int id_player) const;
	Ressources*		get_ressource(unsigned  x, unsigned y) const;
	bool			get_position_unit(Point& ret, Building* building, Lib2D::Control* unit) const;
};

#endif
