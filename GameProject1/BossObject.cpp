
#include "BossObject.h"

BossObject::BossObject()
{
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT * 0.25;
	rect_.h = HEIGHT_BOSS;
	rect_.w = WIDTH_BOSS;
}

BossObject::~BossObject()
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

void BossObject::HandleMove(const int& x_border, const int& y_border)
{
	if (rect_.x > 900)
	{
		rect_.x -= x_val_;
	}

	
}

void BossObject::HandleMoveBackward(const int& x_border, const int& y_border)
{
		rect_.x += x_val_;
		if (rect_.x == x_border + 10)
			rect_.x -= x_val_;
}

void BossObject::HandleInputAction(SDL_Event events)
{

}

void BossObject::InitAmo(AmoObject* p_amo)
{
	if (p_amo)
	{
		bool ret = p_amo->LoadImg(g_name_missile);
		if (ret)
		{
			p_amo->set_is_move(true);
			p_amo->SetWidthHeight(WIDTH_MISSILE, HEIGHT_MISSILE);
			p_amo->set_type(AmoObject::MISSILE);
			p_amo->SetRect(rect_.x, rect_.y /* + rect_.h*0.5 */);
			p_amo->set_x_val(BOSS_MISSILE_SPEED);
			p_amo->set_y_val(BOSS_MISSILE_SPEED);
			p_amo_list_.push_back(p_amo);
		}
	}
}

void BossObject::MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit, double y_amo)
{

	for (int i = 0; i < p_amo_list_.size(); i++)
	{
		
		AmoObject* p_amo = p_amo_list_.at(i);
		if (p_amo)
		{
			if (p_amo->get_is_move())
			{
				p_amo->Show(des);
				p_amo->Boss_HandleMoveRightToLeft();
			}
			else
			{
				p_amo->set_is_move(true);
				p_amo->SetRect(rect_.x, rect_.y + (rect_.h * y_amo));
			}
		}
	}
}

void BossObject::Reset(const int& xboder)
{

}

void BossObject::ResetAmo(AmoObject* p_amo)
{
	p_amo->SetRect(SCREEN_WIDTH, rect_.y);
}

void BossObject::set_clip()
{
	clip_[0].x = 0;
	clip_[0].y = 0;
	clip_[0].w = WIDTH_BOSS;
	clip_[0].h = HEIGHT_BOSS;

	clip_[1].x = WIDTH_BOSS;
	clip_[1].y = 0;
	clip_[1].w = WIDTH_BOSS;
	clip_[1].h = HEIGHT_BOSS;

	clip_[2].x = 2 * WIDTH_BOSS;
	clip_[2].y = 0;
	clip_[2].w = WIDTH_BOSS;
	clip_[2].h = HEIGHT_BOSS;

	clip_[3].x = 3 * WIDTH_BOSS;
	clip_[3].y = 0;
	clip_[3].w = WIDTH_BOSS;
	clip_[3].h = HEIGHT_BOSS;

	clip_[4].x = 4 * WIDTH_BOSS;
	clip_[4].y = 0;
	clip_[4].w = WIDTH_BOSS;
	clip_[4].h = HEIGHT_BOSS;

	clip_[5].x = 5 * WIDTH_BOSS;
	clip_[5].y = 0;
	clip_[5].w = WIDTH_BOSS;
	clip_[5].h = HEIGHT_BOSS;

	clip_[6].x = 6 * WIDTH_BOSS;
	clip_[6].y = 0;
	clip_[6].w = WIDTH_BOSS;
	clip_[6].h = HEIGHT_BOSS;

	clip_[7].x = 7 * WIDTH_BOSS;
	clip_[7].y = 0;
	clip_[7].w = WIDTH_BOSS;
	clip_[7].h = HEIGHT_BOSS;

	clip_[8].x = 8 * WIDTH_BOSS;
	clip_[8].y = 0;
	clip_[8].w = WIDTH_BOSS;
	clip_[8].h = HEIGHT_BOSS;

	clip_[9].x = 9 * WIDTH_BOSS;
	clip_[9].y = 0;
	clip_[9].w = WIDTH_BOSS;
	clip_[9].h = HEIGHT_BOSS;

}

void BossObject::ShowBossObject(SDL_Surface* des)
{
	if (frame_ >= 9)
	{
		frame_ = 0;
	}

	SDLCommonFunc::ApplySurfaceClip(this->p_object_, des, &clip_[frame_], rect_.x, rect_.y);
}