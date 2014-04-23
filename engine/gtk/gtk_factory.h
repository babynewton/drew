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

#ifndef __DRW_GTK_WIDGET_FACTORY_H__
#define __DRW_GTK_WIDGET_FACTORY_H__

#include <gtk/gtk.h>
#include "window.h"
#include "button.h"
#include "box.h"
#include "separator.h"
#include "label.h"

class drwWidgetFactory{
	public:
		static drwWindow* window(void);
		static drwWindow* window(GtkWidget* widget);
		static drwButton* button(void);
		static drwButton* button(GtkWidget* widget);
		static drwBox* hbox(void);
		static drwBox* hbox(GtkWidget* widget);
		static drwBox* vbox(void);
		static drwBox* vbox(GtkWidget* widget);
		static drwSeparator* hseparator(void);
		static drwSeparator* hseparator(GtkWidget* widget);
		static drwSeparator* vseparator(void);
		static drwSeparator* vseparator(GtkWidget* widget);
		static drwLabel* label(void);
		static drwLabel* label(GtkWidget* widget);
};

#endif //__DRW_GTK_WIDGET_FACTORY_H__


