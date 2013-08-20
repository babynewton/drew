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

#include <string>
#include <iostream>
#include "gtk_window.h"
#include "gtk_button.h"
#include "runtime.h"

using namespace std;

gboolean drwGtkWindow::callback_with_event(GtkWidget* widget, GdkEvent* event, gpointer data){
	drwRuntime* rt = drwRuntimeFactory::create();
	bool bval = FALSE;
	try{
		rt->run((const char*) data, 1);
		bval = rt->result();
	}catch(exception& e){
		cerr << "[error]" << e.what() << endl;
	}
	delete rt;
	return bval;
}

void drwGtkWindow::callback(GtkWidget* widget, gpointer data){
	drwRuntime* rt = drwRuntimeFactory::create();
	try{
		rt->run((const char*) data);
	}catch(exception& e){
		cerr << "[error]" << e.what() << endl;
	}
	delete rt;
}

drwGtkWindow::drwGtkWindow():drwGtkContainer(){
	m_widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_show(m_widget);
}

void drwGtkWindow::border(int border){
	m_log << verbose << "drwGtkWindow::border(" << border << ")" << eol;
	gtk_container_set_border_width(GTK_CONTAINER(m_widget), border);
}
void drwGtkWindow::before_destroy_cb(string& code){
	m_log << verbose << "drwGtkWindow::before_destroy_cb(" << code << ")" << eol;
	m_before_destroy_cb = code;
	gtk_signal_connect(GTK_OBJECT(m_widget), "delete-event", G_CALLBACK(callback_with_event), (gpointer)m_before_destroy_cb.c_str());
}

void drwGtkWindow::on_destroy_cb(string& code){
	m_log << verbose << "drwGtkWindow::on_destroy_cb(" << code << ")" << eol;
	m_on_destroy_cb = code;
	gtk_signal_connect(GTK_OBJECT(m_widget), "destroy", G_CALLBACK(callback), (gpointer)m_on_destroy_cb.c_str());
}

drwWidget* drwGtkWindow::to_widget(void){
	return (drwWidget*)this;
}

drwContainer* drwGtkWindow::to_container(void){
	return (drwContainer*)this;
}
