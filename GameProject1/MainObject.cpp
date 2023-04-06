
#include "MainObject.h"

MainObject::MainObject()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val_ = 0;
	y_val_ = 0;
}

MainObject::~MainObject()
{

}

void MainObject::HandleInputAction(SDL_Event events)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_w:
			y_val_ -= HEIGHT_MAIN_OBJECT/8;
			//Todo
			break;
		case SDLK_s:
			y_val_ += HEIGHT_MAIN_OBJECT/8;
			//Todo
			break;
		case SDLK_d:
			x_val_ += WIDTH_MAIN_OBJECT/8;
			//Todo
			break;
		case SDLK_a:
			x_val_ -= WIDTH_MAIN_OBJECT/8;
			break;
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch(events.key.keysym.sym )
		{
			case SDLK_w: y_val_ += HEIGHT_MAIN_OBJECT/8; break;
			case SDLK_s: y_val_ -= HEIGHT_MAIN_OBJECT/8; break;
			case SDLK_a: x_val_ += WIDTH_MAIN_OBJECT/8; break;
			case SDLK_d: x_val_ -= WIDTH_MAIN_OBJECT/8; break;
		}
	}
	else if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		AmoObject* p_amo = new AmoObject();

		if (events.button.button == SDL_BUTTON_LEFT)
		{
			p_amo->SetWidthHeight(WIDTH_LASER, HEIGHT_LASER);
			p_amo->LoadImg("gfx/laser.png");
			p_amo->set_type(AmoObject::LASER);
		}

		else if (events.button.button == SDL_BUTTON_RIGHT)
		{
			p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->LoadImg("gfx/sphere.png");
			p_amo->set_type(AmoObject::SPHERE);
		}

		p_amo->SetRect(this->rect_.x + this->rect_.w - 20, this->rect_.y + this->rect_.h*0.5);
		p_amo->set_is_move(true);
		p_amo->set_x_val(20);
		p_amo_list_.push_back(p_amo);
	}

	else if (events.type == SDL_MOUSEBUTTONUP)
	{

	}

	else
	{
		;//
	}
}

void MainObject::MakeAmo(SDL_Surface* des)
{
	for (int i = 0; i < p_amo_list_.size(); i++)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if (p_amo != NULL)
		{
			if (p_amo->get_is_move())
			{
				p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_amo->Show(des);
			}
			else
			{
				if (p_amo != NULL)
				{
					p_amo_list_.erase(p_amo_list_.begin() + i);

					delete p_amo;
					p_amo = NULL;
				}
			}
		}
	}
}

void MainObject::HandleMove()
{
	rect_.x += x_val_;

	if (rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH)
	{
		rect_.x -= x_val_;
	}


	rect_.y += y_val_;
	if (rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT)
	{
		rect_.y -= y_val_;
	}
}

void MainObject::RemoveAmo(const int& idx)
{

	for (int i = 0; i < p_amo_list_.size(); i++)
	{
		if (idx < p_amo_list_.size())
		{
			AmoObject* p_amo = p_amo_list_.at(idx);
			p_amo_list_.erase(p_amo_list_.begin() + idx);

			if (p_amo != NULL)
			{
				delete p_amo;
				p_amo = NULL;
			}
		}
	}
}