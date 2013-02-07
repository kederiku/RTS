#include "map.h"
#include "buffer.h"
#include "ns_var.h"
#include "ressources.h"
#include "building.h"
#include "s_ressources.h"
#include "building.h"
#include "unit.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <new>



Map::Map(void):	__nb_ressource(0),
		__case(0),
		__info_resource(0),
		__begin_pos(0)
{
}

Map::~Map(void)
{
	this->clear();
}

bool	Map::init_case_map(int fd, unsigned short int width, unsigned short int height)
{
	Case_map*	buf;
	int		size_file((width * height));
	int		nread;

	buf = new (std::nothrow) Case_map[size_file];
	if (buf == 0)
		return false;
	nread = read(fd, buf, size_file * sizeof(Case_map));
	if (size_file * (int)sizeof(Case_map) < nread)
	{
		this->clear();
		return false;
	}
	else
	{
		delete this->__case;
		this->__case = buf;
	}
	return true;
}

bool	Map::init_ressource(int fd, unsigned short int size)
{
	data_ressource*	buf;
	int		size_file(size);
	int		nread;

	buf = new (std::nothrow) data_ressource[size_file];
	if (buf == 0)
		return false;
	nread = read(fd, buf, size_file * sizeof(data_ressource));
	if (size_file * (int)sizeof(data_ressource) < nread)
	{
		this->clear();
		return false;
	}
	else
	{
		delete this->__info_resource;
		this->__info_resource = buf;
	}
	return true;
}


bool	Map::load_file(const char* path)
{
	int			fd;
	unsigned short int	size[4];
	bool			ret(false);
	char			file[100];

	if (ns_cmc::ns_var::f_str_len(path) + ns_cmc::ns_var::f_str_len(MAP_SRC) > 99)
		return false;
	ns_cmc::ns_var::f_str_cpy(file, MAP_SRC);
	ns_cmc::ns_var::f_str_cat(file, path);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return false;
	if (read(fd, size, sizeof(size)) == sizeof(size))
	{
		ret = this->init_case_map(fd, size[1], size[2]);
		if (ret != false)
			ret = this->init_ressource(fd, size[3]);
		if (ret != false)
		{
			this->__size_case = size[0];
			this->__width = size[1];
			this->__height = size[2];
			this->__nb_ressource = size[3];
		}
	}
	close(fd);
	return ret;
}

bool	Map::save_data(int fd, void* data, int size)
{
	if (size == 0)
		return true;
	return write(fd, data, size) == size;
}

bool	Map::save_file(const char* path)
{
	int	fd;
	char	file[100];

	if (ns_cmc::ns_var::f_str_len(path) + ns_cmc::ns_var::f_str_len(MAP_SRC) > 99)
		return false;
	ns_cmc::ns_var::f_str_cpy(file, MAP_SRC);
	ns_cmc::ns_var::f_str_cat(file, path);
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	if (fd == -1)
		return false;
	if (this->save_data(fd, this, 4 * sizeof(unsigned short int)) == false ||
	    this->save_data(fd, this->__case, this->__width * this->__height * sizeof(Case_map)) == false ||
	    this->save_data(fd, this->__info_resource, this->__nb_ressource * sizeof(data_ressource)) == false)
	{
		close(fd);
		return false;
	}
	close(fd);
	return true;
}

bool	Map::init(unsigned short int size_case, unsigned short int width, unsigned short int height)
{
	delete this->__case;
	this->__case = new (std::nothrow) Case_map[width * height];
	if (this->__case == 0)
		return false;
	this->__size_case = size_case;
	this->__width = width;
	this->__height = height;
	return true;
}

void	Map::set_case(unsigned short int x, unsigned short int y, const Point& pos, bool collision)
{
	this->__case[x + y * this->__width].pos_image.x = pos.x;
	this->__case[x + y * this->__width].pos_image.y = pos.y;
	this->__case[x + y * this->__width].collision = collision;
}

bool	Map::is_case_valid(unsigned x, unsigned y) const
{
	if (this->__case == NULL || x >= this->__width || y >= this->__height)
		return false;
	if (this->get_const_case(x, y)->search_collision() == true)
		return false;
	return true;
}

bool	Map::is_case_valid(const Point& tab_pos, const Point& unit_pos, Lib2D::Control* unit) const
{
	if (this->__case == NULL || tab_pos.x >= this->__width || tab_pos.y >= this->__height)
		return false;
	if (unit == 0)
		return true;
	if (this->get_const_case(tab_pos.x, tab_pos.y)->search_collision(unit_pos, unit) == true)
		return false;
	return true;
}

unsigned short int	Map::get_width(void) const
{
	return this->__width;
}

unsigned short int	Map::get_height(void) const
{
	return this->__height;
}

unsigned short int	Map::get_size_case(void) const
{
	return this->__size_case;
}

void	Map::get_pos_img(const Point& search, Point* ret) const
{
	ret->x = this->__case[search.x + search.y * this->__width].pos_image.x;
	ret->y = this->__case[search.x + search.y * this->__width].pos_image.y;
}

bool	Map::is_init(void) const
{
	return this->__case != 0;
}

void		Map::clear(void)
{
	delete [] this->__case;
	this->__case = 0;
	delete [] this->__info_resource;
	this->__info_resource = 0;
	delete [] this->__begin_pos;
	this->__info_resource = 0;
	this->__nb_ressource = 0;
	this->__nb_player = 0;
}

bool		Map::get_ressource(std::vector<data_ressource>& data) const
{
	unsigned	i(0);

	try
	{
		data.reserve(this->__nb_ressource);
	}
	catch (std::exception&)
	{
		return false;
	}
	while (i < this->__nb_ressource)
	{
		data.push_back(this->__info_resource[i]);
		++i;
	}
	return true;
}

bool		Map::add_ressource(const Point& pos, const Point& size, e_ressource ressource, unsigned short int capacity)
{
	data_ressource*	tmp;
	unsigned	i(0);

	tmp = new (std::nothrow) data_ressource[this->__nb_ressource + 1];
	if (tmp == 0)
		return false;
	for (i = 0; i < this->__nb_ressource; ++i)
		tmp[i] = this->__info_resource[i];
	tmp[this->__nb_ressource].pos = pos;
	tmp[this->__nb_ressource].size = size;
	tmp[this->__nb_ressource].ressource = ressource;
	tmp[this->__nb_ressource].capacity = capacity;
	delete this->__info_resource;
	this->__info_resource = tmp;
	++this->__nb_ressource;
	return true;
}

void		Map::set_case_ressource(Point pos, Point size, Ressources* image)
{
	unsigned	x;
	unsigned	y(0);

	pos.x /= this->__size_case;
	pos.y /= this->__size_case;
	size.x /= this->__size_case;
	size.y /= this->__size_case;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			this->get_case(pos.x + x, pos.y + y)->ressource = image;
			++x;
		}
		++y;
	}
}

void		Map::set_building(Building* building)
{
	Point		pos(building->pos().x / this->__size_case, building->pos().y / this->__size_case);
	Point		size(building->pos().w, building->pos().h);
	unsigned	x;
	unsigned	y(0);

	size.x += ((building->pos().x % this->__size_case) != 0) * 32;
	size.y += ((building->pos().y % this->__size_case) != 0) * 32;
	while (y  * 32 < size.y)
	{
		x = 0;
		while (x * 32 < size.x)
		{
			this->get_case(pos.x + x, pos.y + y)->building = building;
			++x;
		}
		++y;
	}
}

bool		Map::check_collision_construction(const Point& build_size, Lib2D::Control* building) const
{
	Point		pos(build_size.x / this->__size_case, build_size.y / this->__size_case);
	Point		size(building->pos().w, building->pos().h);
	unsigned	x;
	unsigned	y(0);

	size.x += ((build_size.x % this->__size_case) != 0) * 32;
	size.y += ((build_size.y % this->__size_case) != 0) * 32;
	while (y * 32 < size.y)
	{
		x = 0;
		while (x * 32 < size.x)
		{
			if (this->is_case_valid(pos.x + x, pos.y + y) == false)
				return true;
			++x;
		}
		++y;
	}
	return false;
}

bool		Map::get_neighbor(const Point& pos, info_pos* neighbor, unsigned& size, Lib2D::Control* unit) const
{
	position	dir[] = {position(0, -1), position(1, 0), position(0, 1), position(-1, 0)};
	bool		diagonal[] = {false, false, false, false, false};
	unsigned	i(0);

	while (i < 4)
	{
		neighbor[size].distance = 10;
		neighbor[size].x = pos.x + dir[i].x;
		neighbor[size].y = pos.y + dir[i].y;
		if (this->is_case_valid(neighbor[size], Point(neighbor[size].x * 32, neighbor[size].y * 32), unit) == true)
		{
			diagonal[i] = true;
			++size;
		}
		++i;
	}
	diagonal[4] = diagonal[0];
	i = 0;
	dir[0].x = 1;
	dir[1].y = 1;
	dir[2].x = -1;
	dir[3].y = -1;
	while (i < 4)
	{
		neighbor[size].distance = 14;
		neighbor[size].x = pos.x + dir[i].x;
		neighbor[size].y = pos.y + dir[i].y;
		if (diagonal[i] && diagonal[i + 1] &&
		    this->is_case_valid(neighbor[size], Point(neighbor[size].x * 32, neighbor[size].y * 32), unit) == true)
			++size;
		++i;
	}
	return true;
}

int	Map::get_distance(const Point& begin, const Point end) const
{
	return 10 * (abs(end.x - begin.x) + abs(end.y - begin.y));
}

Case_map*	Map::get_case(unsigned x, unsigned y)
{
	return this->__case + x + y * this->__width;
}

const Case_map*	Map::get_const_case(unsigned x, unsigned y) const
{
	return this->__case + x + y * this->__width;
}

void	Map::set_unit(unsigned  x, unsigned y, Unit* unit)
{
	this->get_case(x, y)->unit = unit;
}

Unit*	Map::get_unit(unsigned  x, unsigned y, int id_player)
{
	if (this->__case == NULL || x >= this->__width || y >= this->__height)
		return 0;
	if (this->get_case(x, y)->unit == 0)
		return 0;
	if (this->get_case(x, y)->unit->get_id_player() != id_player)
		return 0;
	return this->get_case(x, y)->unit;
}

bool	Map::search_ressource(unsigned  x, unsigned y, e_ressource type) const
{
	if (this->__case == NULL || x >= this->__width || y >= this->__height)
		return false;
	if (this->get_const_case(x, y)->ressource == 0)
		return false;
	return this->get_const_case(x, y)->ressource->get_capacity() > 0 &&
	       this->get_const_case(x, y)->ressource->get_type() == type;
}

bool	Map::search_ressource(Point& ret, unsigned x, unsigned y, unsigned max, e_ressource type) const
{
	for (unsigned i = 0; i < max; ++i)
	{
		if (this->search_ressource(ret.x, ret.y, type) == true)
			return true;
		ret.x += x;
		ret.y += y;
	}
	return false;
}

bool	Map::get_closest_ressource(const Point& begin, Point& ret, e_ressource type) const
{
	unsigned	circle(1);

	ret = begin;
	++ret.x;
	while (circle < 200)
	{
		if (this->search_ressource(ret, 0, 1, circle, type) == true ||
		    this->search_ressource(ret, -1, 0, circle * 2, type) == true ||
		    this->search_ressource(ret, 0, -1, circle * 2, type) == true ||
		    this->search_ressource(ret, 1, 0, circle * 2, type) == true ||
		    this->search_ressource(ret, 0, 1, circle, type) == true)
			return true;
		++ret.x;
		++circle;
	}
	return false;
}

bool	Map::search_town_center(unsigned  x, unsigned y, int id_player) const
{
	if (this->__case == NULL || x >= this->__width || y >= this->__height)
		return false;
	if (this->get_const_case(x, y)->building == 0)
		return false;
	return this->get_const_case(x, y)->building->get_type() == TOWN_CENTER &&
	       this->get_const_case(x, y)->building->get_id_player() == id_player;
}

bool	Map::search_town_center(Point& ret, unsigned x, unsigned y, unsigned max, int id_player) const
{
	for (unsigned i = 0; i < max; ++i)
	{
		if (this->search_town_center(ret.x, ret.y, id_player) == true)
			return true;
		ret.x += x;
		ret.y += y;
	}
	return false;
}

bool	Map::get_closest_towncenter(const Point& begin, Point& ret, int id_player) const
{
	unsigned	circle(1);

	ret = begin;
	++ret.x;
	while (circle < 200)
	{
		if (this->search_town_center(ret, 0, 1, circle, id_player) == true ||
		    this->search_town_center(ret, -1, 0, circle * 2, id_player) == true ||
		    this->search_town_center(ret, 0, -1, circle * 2, id_player) == true ||
		    this->search_town_center(ret, 1, 0, circle * 2, id_player) == true ||
		    this->search_town_center(ret, 0, 1, circle, id_player) == true)
			return true;
		++ret.x;
		++circle;
	}
	return false;
}

Ressources*	Map::get_ressource(unsigned  x, unsigned y) const
{
	if (this->__case == NULL || x >= this->__width || y >= this->__height)
		return 0;
	return this->get_const_case(x, y)->ressource;
}


bool	Map::search_pos_unit(Point& ret, unsigned x, unsigned y, unsigned max, Lib2D::Control* unit) const
{
	for (unsigned i = 0; i < max; ++i, ret.x += x, ret.y += y)
	{
		if (this->is_case_valid(ret, Point(ret * 32), unit) == true)
			return true;
	}
	return false;
}

bool	Map::get_position_unit(Point& ret, Building* building, Lib2D::Control* unit) const
{
	ret.x = (building->pos().x + building->pos().w) / 32 + 1;
	ret.y = (building->pos().y + building->pos().h) / 32 + 1;
	if (this->search_pos_unit(ret, -1, 0, building->pos().w / 16, unit) == true ||
	    this->search_pos_unit(ret, 0, -1, building->pos().h / 16, unit) == true ||
	    this->search_pos_unit(ret, 1, 0, building->pos().w / 16, unit) == true ||
	    this->search_pos_unit(ret, 0, 1, building->pos().h / 16, unit) == true)
	{
		ret *= 32;
		return true;
	}
	return false;
}
