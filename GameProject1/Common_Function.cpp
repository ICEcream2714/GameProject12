
#include "Common_Function.h"
#include "TextObject.h" 

bool SDLCommonFunc::CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
	if (x >= rect.x && x < rect.x + rect.w &&
		y >= rect.y && y <= rect.y + rect.h)
	{
		return true;
	}
	return false;
}

int SDLCommonFunc::ShowMenu(SDL_Surface* des, TTF_Font* font)
{
	g_img_menu = LoadImage(g_name_start_background);
	g_tutorial = LoadImage(g_name_tutorial);

	if (g_img_menu == NULL || g_tutorial == NULL)
	{
		return 1;
	}

	bool check_tutorial = false;

	// Set text on MainMenu
	const int kMenuItemNum = 3;

	SDL_Rect pos_arr[kMenuItemNum];
	pos_arr[0].x = 490;
	pos_arr[0].y = 300;

	pos_arr[1].x = 505;
	pos_arr[1].y = 380;

	pos_arr[2].x = 570;
	pos_arr[2].y = 460;

	TextObject text_menu[kMenuItemNum];

	text_menu[0].SetText("Play Game");
	text_menu[0].SetColor(TextObject::WHITE_TEXT);
	text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

	text_menu[1].SetText("Tutorial");
	text_menu[1].SetColor(TextObject::WHITE_TEXT);
	text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

	text_menu[2].SetText("Exit");
	text_menu[2].SetColor(TextObject::WHITE_TEXT);
	text_menu[2].SetRect(pos_arr[2].x, pos_arr[2].y);


	bool selected[kMenuItemNum] = { 0, 0, 0 };

	int xm = 0;
	int ym = 0;


	SDL_Event m_event;
	while (true)
	{
		SDLCommonFunc::ApplySurface(g_img_menu, des, 0, 0);

		for (int i = 0; i < kMenuItemNum; i++)
		{
			text_menu[i].CreateGameText(font, des);
		}

		while (SDL_PollEvent(&m_event))
		{
			switch (m_event.type)
			{
			case SDL_QUIT:
				return 1;
			case SDL_MOUSEMOTION:
			{
				xm = m_event.motion.x;
				ym = m_event.motion.y;

				for (int i = 0; i < kMenuItemNum; i++)
				{
					if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
					{
						if (selected[i] == false)
						{
							selected[i] = 1;
							text_menu[i].SetColor(TextObject::RED_TEXT);

						}
					}
					else
					{
						if (selected[i] == true)
						{
							selected[i] = 0;
							text_menu[i].SetColor(TextObject::WHITE_TEXT);

						}
					}
				}

			}
			break;

			case SDL_MOUSEBUTTONDOWN:
			{
				xm = m_event.button.x;
				ym = m_event.button.y;

				bool mouse_start = CheckFocusWithRect(xm, ym, text_menu[0].GetRect());
				bool mouse_tutorial = CheckFocusWithRect(xm, ym, text_menu[1].GetRect());
				bool mouse_exit = CheckFocusWithRect(xm, ym, text_menu[2].GetRect());

				if (mouse_start)
					return 0;
				else if (mouse_exit)
					return 1;
				else if (mouse_tutorial)
				{
					check_tutorial = true;
				}

			}
				break;

			case SDL_KEYDOWN:
				if (m_event.key.keysym.sym == SDLK_ESCAPE)
				{
					check_tutorial = false;
				}
			break;

			default:
				break;
			}
		}
		if (check_tutorial)
		{
			SDLCommonFunc::ApplySurface(g_tutorial, des, 160, 90);
		}

		SDL_Flip(des);
	}
	return 1;
}




SDL_Surface* SDLCommonFunc::LoadImage(std::string file_path)
{
	SDL_Surface * load_image = NULL;
	SDL_Surface* optimize_image = NULL;
	load_image = IMG_Load(file_path.c_str());
	if (load_image != NULL)
	{
		optimize_image= SDL_DisplayFormat(load_image);
		SDL_FreeSurface(load_image);

		if (optimize_image != NULL) 
		{
			UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 255, 255);
			SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
		}
	}
	return optimize_image;
}


SDL_Rect SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, des, &offset);

	return offset;
}


void SDLCommonFunc::ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, clip, des, &offset);

}


bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
	int left_a = object1.x;
	int right_a = object1.x + object1.w;
	int top_a = object1.y;
	int bottom_a = object1.y + object1.h;

	int left_b = object2.x;
	int right_b = object2.x + object2.w;
	int top_b = object2.y;
	int bottom_b = object2.y + object2.h;

	// Case 1: size object 1 < size object 2
	if (left_a > left_b && left_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (left_a > left_b && left_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	// Case 2: size object 1 < size object 2
	if (left_b > left_a && left_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (left_b > left_a && left_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	// Case 3: size object 1 = size object 2
	if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
	{
		return true;
	}

	return false;
}

void SDLCommonFunc::CleanUp()
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_bkground);


}

