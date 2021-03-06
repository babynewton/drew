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
	return wnd;
}

drwButton* drwWidgetFactory::button(void){
	return button(gtk_button_new());
}

drwButton* drwWidgetFactory::button(GtkWidget* widget){
	drwButton* btn = new drwButton();
	btn->m_handle = widget;
	btn->m_type = DRW_WIDGET_TYPE_BUTTON;
	return btn;
}

drwBox* drwWidgetFactory::hbox(){
	drwBox* box = new drwBox();
	box->m_type = DRW_WIDGET_TYPE_HBOX;
	return vbox(gtk_hbox_new(false, 0));
}

drwBox* drwWidgetFactory::hbox(GtkWidget* widget){
	drwBox* box = new drwBox();
	box->m_handle = widget;
	box->m_type = DRW_WIDGET_TYPE_HBOX;
	return box;
}

drwBox* drwWidgetFactory::vbox(){
	drwBox* box = new drwBox();
	box->m_type = DRW_WIDGET_TYPE_VBOX;
	return vbox(gtk_vbox_new(false, 0));
}

drwBox* drwWidgetFactory::vbox(GtkWidget* widget){
	drwBox* box = new drwBox();
	box->m_handle = widget;
	box->m_type = DRW_WIDGET_TYPE_VBOX;
	return box;
}

drwSeparator* drwWidgetFactory::hseparator(void){
	return hseparator(gtk_hseparator_new());
}

drwSeparator* drwWidgetFactory::hseparator(GtkWidget* widget){
	drwSeparator* hsep = new drwSeparator();
	hsep->m_handle = widget;
	hsep->m_type = DRW_WIDGET_TYPE_HSEPARATOR;
	return hsep;
}

drwSeparator* drwWidgetFactory::vseparator(void){
	return vseparator(gtk_vseparator_new());
}

drwSeparator* drwWidgetFactory::vseparator(GtkWidget* widget){
	drwSeparator* vsep = new drwSeparator();
	vsep->m_handle = widget;
	vsep->m_type = DRW_WIDGET_TYPE_VSEPARATOR;
	return vsep;
}

drwLabel* drwWidgetFactory::label(void){
	return label(gtk_label_new(NULL));
}

drwLabel* drwWidgetFactory::label(GtkWidget* widget){
	drwLabel* lbl = new drwLabel();
	lbl->m_handle = widget;
	lbl->m_type = DRW_WIDGET_TYPE_LABEL;
	return lbl;
}

