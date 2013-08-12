#ifndef __DRW_ENGINE_H__
#define __DRW_ENGINE_H__

#include "window.h"
#include "button.h"

class drwEngine{
	private:
		drwWindow* m_window;
	public:
		static drwWindow* new_window(void);
		static drwButton* new_button(void);
		drwEngine();
		void add(drwWindow* window);
		void run(void);
};

#endif //__DRW_ENGINE_H__
