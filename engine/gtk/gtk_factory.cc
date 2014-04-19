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

#include "gtk_factory.h"

drwWindow* drwWidgetFactory::window(void){
	return window(gtk_window_new(GTK_WINDOW_TOPLEVEL));
}

drwWindow* drwWidgetFactory::window(GtkWidget* widget){
	drwWindow* wnd = new drwWindow();
	wnd->m_handle = widget;
	wnd->m_type = DRW_WIDGET_TYPE_WINDOW;
	gtk_widget_show(GTK_WIDGET(wnd->m_handle));
	return wnd;
}

drwButton* drwWidgetFactory::button(void){
	return button(gtk_button_new());
}

drwButton* drwWidgetFactory::button(GtkWidget* widget){
	drwButton* btn = new drwButton();
	btn->m_handle = widget;
	btn->m_type = DRW_WIDGET_TYPE_BUTTON;
	gtk_widget_show(GTK_WIDGET(btn->m_handle));
	return btn;
}

drwHBox* drwWidgetFactory::hbox(){
	drwHBox* box = new drwHBox();
	box->m_type = DRW_WIDGET_TYPE_HBOX;
	return box;
}

drwHBox* drwWidgetFactory::hbox(GtkWidget* widget){
	drwHBox* box = new drwHBox();
	box->m_handle = widget;
	box->m_type = DRW_WIDGET_TYPE_HBOX;
	gtk_widget_show(GTK_WIDGET(box->m_handle));
	return box;
}

drwVBox* drwWidgetFactory::vbox(){
	drwVBox* box = new drwVBox();
	box->m_type = DRW_WIDGET_TYPE_VBOX;
	return box;
}

drwVBox* drwWidgetFactory::vbox(GtkWidget* widget){
	drwVBox* box = new drwVBox();
	box->m_handle = widget;
	box->m_type = DRW_WIDGET_TYPE_VBOX;
	gtk_widget_show(GTK_WIDGET(box->m_handle));
	return box;
}

