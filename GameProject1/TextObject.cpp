

#include "TextObject.h"

TextObject::TextObject()
{
	rect_.x = 530;
	rect_.y = 10;
	text_color_.r = 255;
	text_color_.g = 255;
	text_color_.b = 255;
}

TextObject::~TextObject()
{

}

void TextObject::SetColor(const int& type)
{
	if (type == RED_TEXT)
	{
		SDL_Color color = { 255, 0, 0 };
		text_color_ = color;
	}
	else if (type == WHITE_TEXT)
	{
		SDL_Color color = { 255, 255, 255 };
		text_color_ = color;
	}
	else
	{
		SDL_Color color = { 0, 0, 0 };
		text_color_ = color;
	}
}

void TextObject::CreateGameText(TTF_Font* font, SDL_Surface* des)
{
	p_object_ = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);
	Show(des);
}