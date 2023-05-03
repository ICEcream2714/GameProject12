
#ifndef BOSS_OBJECT_H_
#define BOSS_OBJECT_H_


#include "Common_Function.h"
#include "BaseObject.h"
#include "AmoObject.h"
#include <vector>

#define WIDTH_BOSS 215
#define HEIGHT_BOSS 360


class BossObject : public BaseObject
{
public:
	BossObject();
	~BossObject();

	void HandleMove(const int& x_border, const int& y_border);
	void HandleMoveBackward(const int& x_border, const int& y_border);
	void HandleInputAction(SDL_Event events);

	void set_x_val(const int& val)
	{
		x_val_ = val;
	}
	void set_y_val(const int& val)
	{
		y_val_ = val;
	}
	int get_x_val() const { return x_val_; }
	int get_y_val() const { return y_val_; }

	void SetAmoList(std::vector<AmoObject*> amo_list) { p_amo_list_ = amo_list; }
	std::vector<AmoObject*> GetAmoList() const { return p_amo_list_; }

	void InitAmo(AmoObject* p_amo);
	void MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit, double y_amo);

	void Reset(const int& xboder);
	void ResetAmo(AmoObject* p_amo);

	void set_clip();
	void set_frame(const int& fr) { frame_ = fr; }
	void ShowBossObject(SDL_Surface* des);


private:
	int x_val_;
	int y_val_;

	int frame_;
	SDL_Rect clip_[10];

	std::vector<AmoObject*> p_amo_list_;
};




#endif
