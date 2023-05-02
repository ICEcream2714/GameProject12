
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
		bool ret = p_amo->LoadImg(g_name_amo_3);
		if (ret)
		{
			p_amo->set_is_move(true);
			p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->set_type(AmoObject::SPHERE);
			p_amo->SetRect(rect_.x, rect_.y + rect_.h*0.5);
			p_amo->set_x_val(THREAT_AMO_SPEED);
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

	int rand_y = rand() % 600 + 40;
	if (rand_y > SCREEN_HEIGHT)
	{
		rand_y = SCREEN_HEIGHT * 0.3;
	}
	rect_.y = rand_y;

}


void ThreatsObject::ResetAmo(AmoObject* p_amo)
{
	p_amo->SetRect(rect_.x, rect_.y + rect_.h*0.5);
}

void ThreatsObject::set_clip()
{
	clip_[0].x = 0;
	clip_[0].y = 0;
	clip_[0].w = WIDTH_THREAT;
	clip_[0].h = HEIGHT_THREAT;

	clip_[1].x = WIDTH_THREAT;
	clip_[1].y = 0;
	clip_[1].w = WIDTH_THREAT;
	clip_[1].h = HEIGHT_THREAT;

	clip_[2].x = 2 * WIDTH_THREAT;
	clip_[2].y = 0;
	clip_[2].w = WIDTH_THREAT;
	clip_[2].h = HEIGHT_THREAT;

	clip_[3].x = 3 * WIDTH_THREAT;
	clip_[3].y = 0;
	clip_[3].w = WIDTH_THREAT;
	clip_[3].h = HEIGHT_THREAT;

	clip_[4].x = 4 * WIDTH_THREAT;
	clip_[4].y = 0;
	clip_[4].w = WIDTH_THREAT;
	clip_[4].h = HEIGHT_THREAT;

	clip_[5].x = 5 * WIDTH_THREAT;
	clip_[5].y = 0;
	clip_[5].w = WIDTH_THREAT;
	clip_[5].h = HEIGHT_THREAT;

	clip_[6].x = 6 * WIDTH_THREAT;
	clip_[6].y = 0;
	clip_[6].w = WIDTH_THREAT;
	clip_[6].h = HEIGHT_THREAT;

	clip_[7].x = 7 * WIDTH_THREAT;
	clip_[7].y = 0;
	clip_[7].w = WIDTH_THREAT;
	clip_[7].h = HEIGHT_THREAT;

	clip_[8].x = 8 * WIDTH_THREAT;
	clip_[8].y = 0;
	clip_[8].w = WIDTH_THREAT;
	clip_[8].h = HEIGHT_THREAT;

	clip_[9].x = 9 * WIDTH_THREAT;
	clip_[9].y = 0;
	clip_[9].w = WIDTH_THREAT;
	clip_[9].h = HEIGHT_THREAT;

}

void ThreatsObject::ShowThreatObject(SDL_Surface* des)
{
	if (frame_ >= 9)
	{
		frame_ = 0;
	}

	SDLCommonFunc::ApplySurfaceClip(this->p_object_, des, &clip_[frame_], rect_.x, rect_.y);
}