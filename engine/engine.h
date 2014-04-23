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

#include "log.h"
#include <map>
#include <string>
#include <vector>
#include "runtime.h"
#include "window.h"
#include "button.h"
#include "box.h"
#include "hseparator.h"
#include "vseparator.h"
#include "label.h"

using namespace std;

class drwEngine{
	public:
		static drwEngine* instance(void);
		virtual void parse(const string path, vector<string>& arguments) = 0;
		virtual void initialize(int argc, char* argv[]) = 0;
		virtual void add(drwWidget* widget) = 0;
		virtual void run(void) = 0;
		virtual void quit(void) = 0;
		virtual void reserve(drwWidget* widget, const string& wid) = 0;
		virtual DRW_WIDGET_TYPE type(const string& wid) = 0;
		virtual drwWindow* window(void) = 0;
		virtual drwWindow* window(const string& wid) = 0;
		virtual drwButton* button(void) = 0;
		virtual drwButton* button(const string& wid) = 0;
		virtual drwBox* hbox(void) = 0;
		virtual drwBox* hbox(const string& wid) = 0;
		virtual drwBox* vbox(void) = 0;
		virtual drwBox* vbox(const string& wid) = 0;
		virtual drwHSeparator* hseparator(void) = 0;
		virtual drwHSeparator* hseparator(const string& wid) = 0;
		virtual drwVSeparator* vseparator(void) = 0;
		virtual drwVSeparator* vseparator(const string& wid) = 0;
		virtual drwLabel* label(void) = 0;
		virtual drwLabel* label(const string& wid) = 0;
};

#endif //__DRW_ENGINE_H__
