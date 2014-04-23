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

#ifndef __DRW_GTK_ENGINE_H__
#define __DRW_GTK_ENGINE_H__

#include <gtk/gtk.h>
#include "../engine.h"
#include "log.h"
#include <map>

using namespace std;

class drwGtkEngine : public drwEngine{
	private:
		GtkWidget* m_top;
		drwLog& m_log;
		map<string, GtkWidget*> m_cache;
		void cache(GtkWidget* widget, const string& wid);
		GtkWidget* cache(const string& wid);
	public:
		drwGtkEngine();
		void parse(const string path, vector<string>& arguments);
		void initialize(int argc, char* argv[]);
		void add(drwWidget* widget);
		void run(void);
		void quit(void);
		void reserve(drwWidget* wgt, const string& wid);
		DRW_WIDGET_TYPE type(const string& wid);
		drwWindow* window(void);
		drwWindow* window(const string& wid);
		drwButton* button(void);
		drwButton* button(const string& wid);
		drwBox* hbox(void);
		drwBox* hbox(const string& wid);
		drwBox* vbox(void);
		drwBox* vbox(const string& wid);
		drwSeparator* hseparator(void);
		drwSeparator* hseparator(const string& wid);
		drwSeparator* vseparator(void);
		drwSeparator* vseparator(const string& wid);
		drwLabel* label(void);
		drwLabel* label(const string& wid);
};

#endif //__DRW_GTK_ENGINE_H__
