#ifndef __DRW_WINDOW_H__
#define __DRW_WINDOW_H__

#include <string>
#include "widget.h"

using namespace std;

//TODO:we can do  it by smart pointer
class drwWindow{
	public:
		virtual void border(int border) = 0;
		virtual void before_destroy_cb(string& code) = 0;
		virtual void on_destroy_cb(string& code) = 0;
		virtual drwWidget* to_widget(void) = 0;
};
#endif //__DRW_WINDOW_H__
