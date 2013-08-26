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
#include "gtk_button.h"

void drwGtkButton::click_callback(GtkWidget* widget, gpointer data){
	drwGtkButton* btn = (drwGtkButton*)data;
	drwRuntime* rt = drwRuntimeFactory::create();
	try{
		btn->prepare_runtime(rt);
		rt->run(btn->click_cb().c_str());
	}catch(exception& e){
		cerr << "[error] " << e.what() << endl;
	}
	delete rt;
}

drwGtkButton::drwGtkButton():drwGtkContainer(){
	m_widget = gtk_button_new();
	gtk_widget_show(m_widget);
}

void drwGtkButton::label(string& lbl){
	gtk_button_set_label(GTK_BUTTON(m_widget), lbl.c_str());
}

void drwGtkButton::click_cb(string& code){
	m_log << verbose << "drwGtkButton::click_cb(" << code << ")" << eol;
	m_click_cb = code;
	gtk_signal_connect(GTK_OBJECT(m_widget), "clicked", G_CALLBACK(click_callback), (gpointer)this);
}

string& drwGtkButton::click_cb(void){
	return m_click_cb;
}

void drwGtkButton::prepare_runtime(drwRuntime* rt){
	//TODO:preparing
}

drwWidget* drwGtkButton::to_widget(void){
	return (drwWidget*)this;
}

drwContainer* drwGtkButton::to_container(void){
	return (drwContainer*)this;
}
