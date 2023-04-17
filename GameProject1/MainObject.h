
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"
#include "AmoObject.h"
#include <vector>

#define WIDTH_MAIN_OBJECT 80
#define HEIGHT_MAIN_OBJECT 80

class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

	void HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2]);
	void HandleMove();
	void SetAmoList(std::vector<AmoObject*> amo_list) {p_amo_list_ = amo_list;}
	std::vector<AmoObject*> GetAmoList() const {return p_amo_list_;}
	
	void MakeAmo(SDL_Surface* des);
	void RemoveAmo(const int& idx);

	void set_clip();
	void set_frame(const int& fr) { frame1_ = fr; }
	void ShowMainObject(SDL_Surface* des);

private:
	int x_val_;
	int y_val_;

	std::vector<AmoObject*> p_amo_list_;

	int frame1_;
	SDL_Rect clip1_[10];

};



#endif //MAIN_OBJECT_H_