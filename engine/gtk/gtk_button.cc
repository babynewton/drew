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

#include <iostream>
#include "../button.h"
#include "runtime.h"

void click_callback(GtkWidget* widget, gpointer data){
	drwButton* btn = (drwButton*)data;
	drwRuntime* rt = new drwRuntime((drwWidget*)btn);
	try{
		rt->run(btn->click_cb().c_str());
	}catch(exception& e){
		cerr << "[error] " << e.what() << endl;
	}
	delete rt;
}

drwButton::drwButton():drwContainer(DRW_WIDGET_TYPE_BUTTON){
	m_handle = gtk_button_new();
	gtk_widget_show(m_handle);
}

drwButton::~drwButton(){}

void drwButton::label(string& lbl){
	gtk_button_set_label(GTK_BUTTON(m_handle), lbl.c_str());
}

void drwButton::click_cb(string& code){
	m_log << verbose << "drwButton::click_cb(" << code << ")" << eol;
	m_click_cb = code;
	gtk_signal_connect(GTK_OBJECT(m_handle), "clicked", G_CALLBACK(click_callback), (gpointer)this);
}

string drwButton::click_cb(void){
	return m_click_cb;
}

