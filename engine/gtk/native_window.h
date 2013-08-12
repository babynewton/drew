#ifndef __DRW_NATIVE_WINDOW_H__
#define __DRW_NATIVE_WINDOW_H__

#include "../window.h"

class drwNativeWindow : public drwWindow{
	private:
		drwLog& m_log;
	public:
		drwNativeWindow();
		void add(drwButton* button);
		void set_border(int border);
		void set_before_destroy_cb(string& cb);
		void set_on_destroy_cb(string& cb);
};

#endif //__DRW_NATIVE_WINDOW_H__
