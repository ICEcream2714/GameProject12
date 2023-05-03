
#include "ItemObject.h"

ItemObject::ItemObject()
{
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT * 0.5;
	rect_.h = HEIGHT_HEALTH_ITEM;
	rect_.w = WIDTH_HEALTH_ITEM;
}

ItemObject::~ItemObject()
{

}

void ItemObject::HandleMove(const int& x_border, const int& y_border)
{
	if (rect_.x > 0)
	{
		rect_.x -= x_val_;
	}
}

void ItemObject::Reset(const int& xboder)
{
	rect_.x = SCREEN_WIDTH;
	int rand_y = rand() % 600 + 60;
	rect_.y = rand_y;
}

void ItemObject::ShowItemObject(SDL_Surface* des)
{
	
}