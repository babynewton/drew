#ifndef __DRW_WINDOW_H__
#define __DRW_WINDOW_H__

#include "button.h"

class drwWindow{
	public:
		virtual void add(drwButton* button) = 0;
		virtual void border(int border) = 0;
		virtual void before_destroy_cb(string& code) = 0;
		virtual void on_destroy_cb(string& code) = 0;
};
#endif //__DRW_WINDOW_H__
