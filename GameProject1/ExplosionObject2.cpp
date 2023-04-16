
#include "ExplosionObject2.h"

ExplosionObject_2::ExplosionObject_2()
{

}

ExplosionObject_2::~ExplosionObject_2()
{

}

void ExplosionObject_2::set_clip()
{
	clip_[0].x = 0;
	clip_[0].y = 0;
	clip_[0].w = EXP_WIDTH_2;
	clip_[0].h = EXP_HEIGHT_2;

	clip_[1].x = EXP_WIDTH_2;
	clip_[1].y = 0;
	clip_[1].w = EXP_WIDTH_2;
	clip_[1].h = EXP_HEIGHT_2;

	clip_[2].x = 2 * EXP_WIDTH_2;
	clip_[2].y = 0;
	clip_[2].w = EXP_WIDTH_2;
	clip_[2].h = EXP_HEIGHT_2;

	clip_[3].x = 3 * EXP_WIDTH_2;
	clip_[3].y = 0;
	clip_[3].w = EXP_WIDTH_2;
	clip_[3].h = EXP_HEIGHT_2;

	clip_[4].x = 4 * EXP_WIDTH_2;
	clip_[4].y = 0;
	clip_[4].w = EXP_WIDTH_2;
	clip_[4].h = EXP_HEIGHT_2;

	clip_[5].x = 5 * EXP_WIDTH_2;
	clip_[5].y = 0;
	clip_[5].w = EXP_WIDTH_2;
	clip_[5].h = EXP_HEIGHT_2;

	clip_[6].x = 6 * EXP_WIDTH_2;
	clip_[6].y = 0;
	clip_[6].w = EXP_WIDTH_2;
	clip_[6].h = EXP_HEIGHT_2;

	clip_[7].x = 7 * EXP_WIDTH_2;
	clip_[7].y = 0;
	clip_[7].w = EXP_WIDTH_2;
	clip_[7].h = EXP_HEIGHT_2;


}

void ExplosionObject_2::ShowEx(SDL_Surface* des)
{
	if (frame_ > 7)
	{
		frame_ = 0;
	}

	SDLCommonFunc::ApplySurfaceClip(this->p_object_, des, &clip_[frame_], rect_.x, rect_.y);
}