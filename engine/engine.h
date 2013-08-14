#ifndef __DRW_ENGINE_H__
#define __DRW_ENGINE_H__

#include "window.h"
#include "button.h"
#include "log.h"

class drwEngine{
	private:
		drwWindow* m_window;
		drwLog& m_log;
	public:
		static drwWindow* new_window(void);
		static drwButton* new_button(void);
		drwEngine(int argc, char* argv[]);
		void add(drwWindow* window);
		void run(void);
		void quit(void);
		drwWindow* window(void);
};

#endif //__DRW_ENGINE_H__
