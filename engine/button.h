#ifndef __DRW_BUTTON_H__
#define __DRW_BUTTON_H__

#include "widget.h"
#include <string>

using namespace std;

class drwButton{
	public:
		virtual void label(string& lbl) = 0;
		virtual void click_cb(string& code) = 0;
		virtual drwWidget* to_widget(void) = 0;
};
#endif //__DRW_BUTTON_H__
