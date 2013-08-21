/*
The MIT License (MIT)

Copyright (c) 2013 Newton Kim

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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
		static drwEngine* current(void);
		drwEngine(int argc, char* argv[]);
		void add(drwWindow* window);
		void run(void);
		void quit(void);
		drwWindow* window(void);
};

#endif //__DRW_ENGINE_H__
