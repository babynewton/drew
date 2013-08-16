/*
The MIT License (MIT)

Copyright (c) 2013 drew

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
#include "gtk_button.h"
#include "runtime.h"

void drwGtkButton::callback(GtkWidget* widget, gpointer data){
	drwRuntime* rt = drwRuntimeFactory::create();
	try{
		rt->run((const char*) data);
	}catch(exception& e){
		cerr << "[error] " << e.what() << endl;
	}
	delete rt;
}

drwGtkButton::drwGtkButton():drwGtkWidget(){
	m_widget = gtk_button_new();
	gtk_widget_show(m_widget);
}

void drwGtkButton::label(string& lbl){
	gtk_button_set_label(GTK_BUTTON(m_widget), lbl.c_str());
}

void drwGtkButton::click_cb(string& code){
	m_log << verbose << "drwGtkButton::click_cb(" << code << ")" << eol;
	m_click_cb = code;
	gtk_signal_connect(GTK_OBJECT(m_widget), "clicked", G_CALLBACK(callback), (gpointer)m_click_cb.c_str());
}

drwWidget* drwGtkButton::to_widget(void){
	return (drwWidget*)this;
}
