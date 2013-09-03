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
#include "../window.h"
#include "engine.h"

using namespace std;

gboolean before_destroy_callback(GtkWidget* widget, GdkEvent* event, gpointer data){
	drwWindow* wnd = (drwWindow*)data;
	drwEngine* engine = drwEngine::current();
	drwThread* rt = engine->thread((drwWidget*)wnd);
	bool bval = FALSE;
	try{
		rt->run(wnd->before_destroy_cb().c_str(), 1);
		bval = rt->result();
	}catch(exception& e){
		cerr << "[error]" << e.what() << endl;
	}
	delete rt;
	return bval;
}

void destroy_callback(GtkWidget* widget, gpointer data){
	drwWindow* wnd = (drwWindow*)data;
	drwEngine* engine = drwEngine::current();
	drwThread* rt = engine->thread((drwWidget*)wnd);
	try{
		rt->run(wnd->on_destroy_cb().c_str());
	}catch(exception& e){
		cerr << "[error]" << e.what() << endl;
	}
	delete rt;
}

drwWindow::drwWindow():drwContainer(DRW_WIDGET_TYPE_WINDOW){
	m_handle = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_show(m_handle);
}

drwWindow::~drwWindow(){ }

void drwWindow::title(string& text){
	title(text.c_str());
}

void drwWindow::title(const char* text){
	m_log << verbose << "drwWindow::title(" << text << ")" << eol;
	gtk_window_set_title(GTK_WINDOW(m_handle), text);
}

string drwWindow::title(void){
	return gtk_window_get_title(GTK_WINDOW(m_handle));
}

void drwWindow::border(int border){
	m_log << verbose << "drwWindow::border(" << border << ")" << eol;
	gtk_container_set_border_width(GTK_CONTAINER(m_handle), border);
}

void drwWindow::before_destroy_cb(string& code){
	m_log << verbose << "drwWindow::before_destroy_cb(" << code << ")" << eol;
	m_before_destroy_cb = code;
	gtk_signal_connect(GTK_OBJECT(m_handle), "delete-event", G_CALLBACK(before_destroy_callback), (gpointer)this);
}

string drwWindow::before_destroy_cb(void){
	return m_before_destroy_cb;
}

void drwWindow::on_destroy_cb(string& code){
	m_log << verbose << "drwWindow::on_destroy_cb(" << code << ")" << eol;
	m_on_destroy_cb = code;
	gtk_signal_connect(GTK_OBJECT(m_handle), "destroy", G_CALLBACK(destroy_callback), (gpointer)this);
}

string drwWindow::on_destroy_cb(void){
	return m_on_destroy_cb;
}

