#ifndef __DRW_WINDOW_H__
#define __DRW_WINDOW_H__

#include "button.h"
#include "log.h"

class drwWindow{
	public:
		virtual void add(drwButton* button) = 0;
		virtual void set_border(int border) = 0;
		virtual void set_before_destroy_cb(string& cb) = 0;
		virtual void set_on_destroy_cb(string& cb) = 0;
};
#endif //__DRW_WINDOW_H__
