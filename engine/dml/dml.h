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

#ifndef __DRW_DML_H__
#define __DRW_DML_H__

#include <string>
#include <stack>
#include "log.h"
#include "engine.h"
#include "dml_parser.h"
#include "application_parser.h"
#include "window_parser.h"
#include "button_parser.h"

using namespace std;

class drwDml : public drwDmlCallback{
	private:
		drwLog m_log;
		drwEngine* m_engine;
		stack<drwDmlCallback*> m_stack;
		drwApplicationParser m_application;
		drwWindowParser m_window;
		drwButtonParser m_button;
		drwWindow* m_window_widget;
		drwButton* m_button_widget;

	public:
		drwDml(drwEngine* engine);
		void parse(const string path);
		void onValue(const string name, const int value);
		void onValue(const string name, const double value);
		void onValue(const string name, const string value);
		void onValue(const string name, const bool value);
		void onScript(const string name, const string script);
		void onStructureOpen(const string name);
		void onStructureClose(void);
		void onEnd(void);
};

#endif //__DRW_DML_H__