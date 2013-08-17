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

#ifndef __DRW_NATIVE_WINDOW_H__
#define __DRW_NATIVE_WINDOW_H__

#include "../window.h"
#include "log.h"
#include "gtk_widget.h"
#include <gtk/gtk.h>

class drwGtkWindow : public drwGtkWidget, drwWindow{
	private:
		string m_before_destroy_cb;
		string m_on_destroy_cb;
		static gboolean callback_with_event(GtkWidget* widget, GdkEvent* event, gpointer data);
		static void callback(GtkWidget* widget, gpointer data);
	public:
		drwGtkWindow();
		void border(int border);
		void before_destroy_cb(string& cb);
		void on_destroy_cb(string& cb);
		drwWidget* to_widget(void);
};

#endif //__DRW_NATIVE_WINDOW_H__
