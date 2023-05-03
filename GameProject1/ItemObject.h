
#ifndef ITEM_OBJECT_H_
#define ITEM_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"
#include "AmoObject.h"


#define WIDTH_HEALTH_ITEM 40
#define HEIGHT_HEALTH_ITEM 40

class ItemObject : public BaseObject
{
public:
	ItemObject();
	~ItemObject();

	void HandleMove(const int& x_border, const int& y_border);

	void set_x_val(const int& val) {
		x_val_ = val;
	}
	void set_y_val(const int& val) {
		y_val_ = val;
	}

	int get_x_val() const { return x_val_; }
	int get_y_val() const { return y_val_; }

	void Reset(const int& xboder);
	void ShowItemObject(SDL_Surface* des);



private:
	int x_val_;
	int y_val_;



};



#endif // !ITEM_OBJECT_H_
