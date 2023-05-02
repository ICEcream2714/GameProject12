#include "Common_Function.h"
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

void MainObject::HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2], bool &exit)
{

	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_w:
			y_val_ -= MAINOBJECT_MOVE_SPEED;
			//Todo
			break;
		case SDLK_s:
			y_val_ += MAINOBJECT_MOVE_SPEED;
			//Todo
			break;
		case SDLK_d:
			x_val_ += MAINOBJECT_MOVE_SPEED;
			//Todo
			break;
		case SDLK_a:
			x_val_ -= MAINOBJECT_MOVE_SPEED;
			break;
		case SDLK_ESCAPE:
			exit = !exit;
			break;
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch(events.key.keysym.sym )
		{
		case SDLK_w: y_val_ += MAINOBJECT_MOVE_SPEED; break;
		case SDLK_s: y_val_ -= MAINOBJECT_MOVE_SPEED; break;
		case SDLK_a: x_val_ += MAINOBJECT_MOVE_SPEED; break;
		case SDLK_d: x_val_ -= MAINOBJECT_MOVE_SPEED; break;

		}
	}
	else if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		AmoObject* p_amo = new AmoObject();

		if (events.button.button == SDL_BUTTON_LEFT)
		{
			Mix_PlayChannel(-1, bullet_sound[0], 0);

			p_amo->SetWidthHeight(WIDTH_LASER, HEIGHT_LASER);
			p_amo->LoadImg(g_name_amo_1);
			p_amo->set_type(AmoObject::LASER);

			
		}

		else if (events.button.button == SDL_BUTTON_RIGHT)
		{
			Mix_PlayChannel(-1, bullet_sound[1], 0);

			p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->LoadImg(g_name_amo_2);
			p_amo->set_type(AmoObject::SPHERE);

			
		}

		p_amo->SetRect(this->rect_.x + this->rect_.w - 20, this->rect_.y + this->rect_.h*0.5);
		p_amo->set_is_move(true);
		p_amo->set_x_val(MAINOBJECT_AMO_SPEED);
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

void MainObject::set_clip()
{
	clip1_[0].x = 0;
	clip1_[0].y = 0;
	clip1_[0].w = WIDTH_MAIN_OBJECT;
	clip1_[0].h = HEIGHT_MAIN_OBJECT;

	clip1_[1].x = WIDTH_MAIN_OBJECT;
	clip1_[1].y = 0;
	clip1_[1].w = WIDTH_MAIN_OBJECT;
	clip1_[1].h = HEIGHT_MAIN_OBJECT;

	clip1_[2].x = 2 * WIDTH_MAIN_OBJECT;
	clip1_[2].y = 0;
	clip1_[2].w = WIDTH_MAIN_OBJECT;
	clip1_[2].h = HEIGHT_MAIN_OBJECT;

	clip1_[3].x = 3 * WIDTH_MAIN_OBJECT;
	clip1_[3].y = 0;
	clip1_[3].w = WIDTH_MAIN_OBJECT;
	clip1_[3].h = HEIGHT_MAIN_OBJECT;

	clip1_[4].x = 4 * WIDTH_MAIN_OBJECT;
	clip1_[4].y = 0;
	clip1_[4].w = WIDTH_MAIN_OBJECT;
	clip1_[4].h = HEIGHT_MAIN_OBJECT;

	clip1_[5].x = 5 * WIDTH_MAIN_OBJECT;
	clip1_[5].y = 0;
	clip1_[5].w = WIDTH_MAIN_OBJECT;
	clip1_[5].h = HEIGHT_MAIN_OBJECT;

	clip1_[6].x = 6 * WIDTH_MAIN_OBJECT;
	clip1_[6].y = 0;
	clip1_[6].w = WIDTH_MAIN_OBJECT;
	clip1_[6].h = HEIGHT_MAIN_OBJECT;

	clip1_[7].x = 7 * WIDTH_MAIN_OBJECT;
	clip1_[7].y = 0;
	clip1_[7].w = WIDTH_MAIN_OBJECT;
	clip1_[7].h = HEIGHT_MAIN_OBJECT;

	clip1_[8].x = 8 * WIDTH_MAIN_OBJECT;
	clip1_[8].y = 0;
	clip1_[8].w = WIDTH_MAIN_OBJECT;
	clip1_[8].h = HEIGHT_MAIN_OBJECT;

	clip1_[9].x = 9 * WIDTH_MAIN_OBJECT;
	clip1_[9].y = 0;
	clip1_[9].w = WIDTH_MAIN_OBJECT;
	clip1_[9].h = HEIGHT_MAIN_OBJECT;
}

void MainObject::ShowMainObject(SDL_Surface* des)
{
	if (frame1_ >= 10)
		frame1_ = 0;

	SDLCommonFunc::ApplySurfaceClip(this->p_object_, des, &clip1_[frame1_], rect_.x, rect_.y);

}