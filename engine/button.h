#ifndef __DRW_BUTTON_H__
#define __DRW_BUTTON_H__

#include <string>

using namespace std;

class drwButton {
	public:
		virtual void label(string& lbl) = 0;
		virtual void click_cb(string& code) = 0;
};
#endif //__DRW_BUTTON_H__
