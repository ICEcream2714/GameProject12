
#include "ThreatsObject.h"

ThreatsObject::ThreatsObject()
{
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT*0.5;
	rect_.w = WIDTH_THREAT;
	rect_.h = HEIGHT_THREAT;

	x_val_ = 0;
	y_val_ = 0;
}

ThreatsObject::~ThreatsObject()
{
	if (p_amo_list_.size() > 0)
	{
		for (int i = 0; i < p_amo_list_.size(); i++)
		{
			AmoObject* p_amo = p_amo_list_.at(i);
			if (p_amo != NULL)
			{
				delete p_amo;
				p_amo = NULL;
			}
		}
		p_amo_list_.clear();
	}
}

void ThreatsObject::InitAmo(AmoObject* p_amo)
{
	if (p_amo)
	{
		bool ret = p_amo->LoadImg("gfx/sphere2.png");
		if (ret)
		{
			p_amo->set_is_move(true);
			p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->set_type(AmoObject::SPHERE);
			p_amo->SetRect(rect_.x, rect_.y + rect_.h*0.5);
			p_amo->set_x_val(8);
			p_amo_list_.push_back(p_amo);
		}

	}
}

void ThreatsObject::MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit)
{
	for (int i = 0; i < p_amo_list_.size(); i++)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if (p_amo)
		{
			if (p_amo->get_is_move())
			{
				p_amo->Show(des);
				p_amo->HandleMoveRightToLeft();
			}
			else
			{
				p_amo->set_is_move(true);
				p_amo->SetRect(rect_.x, rect_.y + rect_.h*0.5);
			}
		}
	}
}


void ThreatsObject::HandleMove(const int& x_border, const int& y_border)
{
	rect_.x -= x_val_;
	if (rect_.x + rect_.w < 0)
	{
		rect_.x = SCREEN_WIDTH;
		int rand_y = rand() % 600;
		if (rand_y > SCREEN_HEIGHT)
		{
			rand_y = SCREEN_HEIGHT * 0.3;
		}
		rect_.y = rand_y;
	}
}

void ThreatsObject::HandleInputAction(SDL_Event events)
{

}

void ThreatsObject::Reset(const int& xboder)
{
	rect_.x = xboder;

	int rand_y = rand() % 600;
	if (rand_y > SCREEN_HEIGHT)
	{
		rand_y = SCREEN_HEIGHT * 0.3;
	}
	rect_.y = rand_y;

	/*
	for (int i = 0; i < p_amo_list_.size(); i++)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if (p_amo)
		{
			ResetAmo(p_amo);
		}
	}
	*/
}


void ThreatsObject::ResetAmo(AmoObject* p_amo)
{
	p_amo->SetRect(rect_.x, rect_.y + rect_.h*0.5);
}
