#include "map.h"
#include "buffer.h"
#include "case_map.h"
#include "ns_var.h"
#include "ressources.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <new>


Map::Map(void):	__nb_ressource(0),
		__case(0),
		__info_resource(0)
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
		delete buf;
		std::cout << "fichier de mauvaise taille\t" << std::endl;
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
		delete buf;
		std::cout << "fichier de mauvaise taille\t" << std::endl;
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
	else
		std::cout << "fichier comrompu" << std::endl;
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

void	Map::set_case(unsigned short int x, unsigned short int y, const Point& pos, bool colision)
{
	this->__case[x + y * this->__width].pos_image.x = pos.x;
	this->__case[x + y * this->__width].pos_image.y = pos.y;
	this->__case[x + y * this->__width].collision = colision;
	this->__case[x + y * this->__width].init = true;
}

bool	Map::is_case_valid(unsigned short int x, unsigned short int y) const
{
	if (this->__case == NULL || x >= this->__width || y >= this->__height)
		return false;
	return true;
}

void	Map::del_case(unsigned short int x, unsigned short int y)
{
	this->__case[x + y * this->__width].init = false;
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
	this->__nb_ressource = 0;
}

bool		Map::is_case_init(unsigned short int x, unsigned short y) const
{
	return this->__case[x + y * this->__width].init;
}

bool		Map::get_ressource(std::vector<data_ressource>& data, const Point& min, const Point& max) const
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
		if (this->__info_resource[i].pos.x > min.x &&
		    (this->__info_resource[i].pos.x + this->__info_resource[i].size.x) < max.x &&
		    this->__info_resource[i].pos.y > min.y &&
		    (this->__info_resource[i].pos.y + this->__info_resource[i].size.y) < max.y)
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


bool		Map::add_building(const Point& pos, const Point& size, e_type type, unsigned short int player)
{
	data_building*	tmp;
	unsigned	i(0);

	tmp = new (std::nothrow) data_building[this->__nb_building + 1];
	if (tmp == 0)
		return false;
	for (i = 0; i < this->__nb_building; ++i)
		tmp[i] = this->__info_building[i];
	tmp[this->__nb_ressource].pos = pos;
	tmp[this->__nb_ressource].size = size;
	tmp[this->__nb_ressource].building = type;
	tmp[this->__nb_ressource].player = player;
	delete this->__info_building;
	this->__info_building = tmp;
	++this->__nb_building;
	return true;
}
