#include "container_game.h"
#include "ressources.h"
#include "point.h"
#include "ui.hpp"
#include "ui.h"
#include "ns_var.h"
#include "list.hpp"
#include <new>

Container_game::Container_game(void)
{
	this->__pos_container_map.x = 0;
	this->__pos_container_map.y = 0;
}

Container_game::~Container_game(void)
{
}

bool	Container_game::new_case(const Point& sprite, const Point& dest)
{
	Lib2D::Image*	img;

	img = this->__sprite_field.get_image_part(sprite.x, sprite.y, 32, 32);
	if (img == 0)
		return false;
	img->move(dest.x * 32, dest.y * 32);
	if (this->add_child(img) == false)
	{
		delete img;
		return false;
	}
	return true;
}

bool	Container_game::load_cases_map(void)
{
	Point	img_src;
	Point	sprite;
	Point	dest;

	dest.y = 0;
	img_src.y = this->__pos_container_map.y / SIZE_CASE;
	while (dest.y  <= NB_CASE_HEIGHT && dest.y < this->__map.get_height())
	{
		dest.x = 0;
		img_src.x = this->__pos_container_map.x / SIZE_CASE;
		while (dest.x <= NB_CASE_WIDTH && dest.x < this->__map.get_width())
		{
			this->__map.get_pos_img(img_src, &sprite);
			if (this->new_case(sprite , dest) == false)
				return false;
			++dest.x;
			++img_src.x;
		}
		++dest.y;
		++img_src.y;
	}
	return true;
}

bool	Container_game::load_ressource(void)
{
	std::vector<data_ressource>		data;
	std::vector<data_ressource>::iterator	it_begin;
	std::vector<data_ressource>::iterator	it_end;
	Lib2D::Image*				ressource;
	Point					max(this->__pos_container_map);

	max.x += this->_pos.w;
	max.y += this->_pos.h;
	this->__map.get_ressource(data, this->__pos_container_map, max);
	it_begin = data.begin();
	it_end = data.end();
	while (it_begin != it_end)
	{
		switch (it_begin->ressource)
		{
			case WOOD:
				ressource = this->__sprite_ressource.get_image_part(0, 0, 97, 180);
				break;
			case STONE:
				ressource = this->__sprite_ressource.get_image_part(99, 0, 90, 77);
				break;
			case GOLD:
				ressource = this->__sprite_ressource.get_image_part(195, 0, 73, 75);
				break;
			default:
				return false;
		}
		if (ressource == 0)
			return false;
		ressource->move(it_begin->pos.x - this->__pos_container_map.x, it_begin->pos.y - this->__pos_container_map.y);
		ressource->resize(it_begin->size.x, it_begin->size.y);
		if (this->add_child(ressource) == false)
		{
			delete ressource;
			return false;
		}
		++it_begin;
	}
	return true;
}

bool	Container_game::init_map(void)
{
	if (this->load_cases_map() == false)
		return false;
	if (this->load_ressource() == false)
		return false;
	return true;
}

bool	Container_game::init_new_map(void)
{
	Point	sprite(15 * 33, 18 * 33);
	Point	pos;

	pos.y = 0;
	while (pos.y  <= NB_CASE_HEIGHT)
	{
		pos.x = 0;
		while (pos.x <= NB_CASE_WIDTH)
		{
			if (this->new_case(sprite , pos) == false)
				return false;
			++pos.x;
		}
		++pos.y;
	}
	pos.y = 0;
	while (pos.y  < this->__map.get_height())
	{
		pos.x = 0;
		while (pos.x < this->__map.get_width())
		{
			this->__map.set_case(pos.x, pos.y, sprite, false);
			++pos.x;
		}
		++pos.y;
	}
	return true;
}

bool	Container_game::init_container(void)
{

	if (this->__sprite_field.load_bmp(MAP) == false)
		return false;
	if (this->__sprite_ressource.load_bmp(RES) == false)
		return false;
	this->move(0, 0);
	this->__width = this->__map.get_width() * this->__map.get_size_case();
	this->__heigh = this->__map.get_height() * this->__map.get_size_case();
	if (this->__width > WIDTH_GAME)
		this->__width = WIDTH_GAME;
	if (this->__heigh > HEIGHT_GAME)
		this->__heigh = HEIGHT_GAME;
	this->resize(this->__width, this->__heigh);
	if (Container::init() == false)
		return false;
	return true;
}

bool	Container_game::init(int width, int height)
{
	if (this->__map.init(SIZE_CASE, width, height) == false)
		return false;
	if (this->init_container() == false)
		return false;
	if (this->init_new_map() == false)
		return false;
	return true;
}

bool	Container_game::init(const char* path)
{
	if (this->__map.load_file(path) == false)
		return false;
	if (this->init_container() == false)
		return false;
	if (this->init_map() == false)
		return false;
	return true;
}


bool	Container_game::derived_treat_event(Lib2D::Event* event)
{
	if (event->get_type() == Lib2D::E_KEYDOWN_EVENT)
	{
		switch (((Lib2D::Keyboard_event*)event)->get_key_char())
		{
			case 273:
				if (this->__pos_container_map.y - 50 >= 0)
				{
					this->__pos_container_map.y -= 50;
					this->refresh_img();
//					std::cout << "up" << std::endl;
				}
				break;
			case 274:
				if ((this->__pos_container_map.y + 50 + this->__width) < (this->__map.get_height() * SIZE_CASE))
				{
					this->__pos_container_map.y += 50;
					this->refresh_img();
//					std::cout << "down" << std::endl;
				}
				break;
			case 275:
				if ((this->__pos_container_map.x + 50 + this->__heigh) < (this->__map.get_width() * SIZE_CASE))
				{
					this->__pos_container_map.x += 50;
					this->refresh_img();
//					std::cout << "left" << std::endl;
				}
				break;
			case 276:
//				std::cout << "x " << this->__pos_container_map.x << std::endl;
				if (this->__pos_container_map.x - 50 >= 0)
				{
					this->__pos_container_map.x -= 50;
					this->refresh_img();
//					std::cout << "right" << std::endl;
				}
				break;
		}
	}
	return true;
}

bool	Container_game::refresh_img(void)
{
	clear_list(this->_children);
	if (this->init_map() == false)
		return false;
	return true;
}

bool	Container_game::add_field(const Point& sprite, const Point& mouse)
{
	Point	pos(this->__pos_container_map.x / 32, this->__pos_container_map.y / 32);

	pos.x += mouse.x;
	pos.y += mouse.y;
	this->__map.set_case(pos.x, pos.y, sprite, false);
	if (this->refresh_img() == false)
		return false;
	return true;
}

bool	Container_game::save(const char* file)
{
	if (this->__map.is_init() == false)
		return false;
	return this->__map.save_file(file);
}


bool	Container_game::add_sprite(const info_img&, const Point&)
{
	if (this->refresh_img() == false)
		return false;
	return true;
}

bool	Container_game::add_field(const info_img& info, const Point& mouse)
{
	Point	pos(this->__pos_container_map.x, this->__pos_container_map.y);

	pos.x += mouse.x;
	pos.y += mouse.y;
	pos.x /= 32;
	pos.y /= 32;
	this->__map.set_case(pos.x, pos.y, info.sprite_pos, false);
	if (this->refresh_img() == false)
		return false;
	return true;
}


bool	Container_game::add_ressource(const info_img& info, const Point& mouse)
{
	Point	pos(this->__pos_container_map.x, this->__pos_container_map.y);

	pos.x += mouse.x;
	pos.y += mouse.y;
	if (info.sprite_pos.x == 0)
		this->__map.add_ressource(pos, info.img_size, WOOD, 200);
	else if (info.sprite_pos.x == 99)
		this->__map.add_ressource(pos, info.img_size, STONE, 5000);
	else if (info.sprite_pos.x == 195)
		this->__map.add_ressource(pos, info.img_size, GOLD, 10000);
	if (this->refresh_img() == false)
		return false;
	return true;
}

#define WIDTH_SQUARE  32
#define HEIGHT_SQUARE 32


bool	Container_game::check_position(const Point& pos, const Point& target)
{
	if ((target.x >= pos.x + WIDTH_SQUARE) ||
	    (target.x + WIDTH_SQUARE <= pos.x) ||
	    (target.y >= pos.y + HEIGHT_SQUARE) ||
	    (target.y + HEIGHT_SQUARE <= pos.y))
		return false;
	return true;
}
