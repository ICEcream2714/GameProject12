
#ifndef EXPLOSION2_H_
#define EXPLOSION2_H_

#include "BaseObject.h"
#include "Common_Function.h"

const int EXP_WIDTH_2 = 165;
const int EXP_HEIGHT_2 = 165;

class ExplosionObject_2 : public BaseObject
{
public:
	ExplosionObject_2();
	~ExplosionObject_2();
	void set_clip();
	void set_frame(const int& fr) { frame_ = fr; }
	void ShowEx(SDL_Surface* des);

private:
	int frame_;
	SDL_Rect clip_[8];
};

#endif