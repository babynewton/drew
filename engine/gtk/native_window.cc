#include <string>
#include <iostream>
#include "native_window.h"
#include "native_button.h"
#include "runtime.h"

using namespace std;

gboolean drwNativeWindow::callback_with_event(GtkWidget* widget, GdkEvent* event, gpointer data){
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

void drwNativeWindow::callback(GtkWidget* widget, gpointer data){
	drwRuntime* rt = drwRuntimeFactory::create();
	try{
		rt->run((const char*) data);
	}catch(exception& e){
		cerr << "[error]" << e.what() << endl;
	}
	delete rt;
}

drwNativeWindow::drwNativeWindow():m_log(drwLog::instance()), m_widget(gtk_window_new(GTK_WINDOW_TOPLEVEL)){
	gtk_widget_show(m_widget);
}

void drwNativeWindow::add(drwButton* button){
	drwNativeButton* nbtn = (drwNativeButton*) button;
	gtk_container_add(GTK_CONTAINER(m_widget), nbtn->widget());
}

void drwNativeWindow::border(int border){
	m_log << verbose << "drwNativeWindow::border(" << border << ")" << eol;
	gtk_container_set_border_width(GTK_CONTAINER(m_widget), border);
}
void drwNativeWindow::before_destroy_cb(string& code){
	m_log << verbose << "drwNativeWindow::before_destroy_cb(" << code << ")" << eol;
	m_before_destroy_cb = code;
	gtk_signal_connect(GTK_OBJECT(m_widget), "delete-event", G_CALLBACK(callback_with_event), (gpointer)m_before_destroy_cb.c_str());
}

void drwNativeWindow::on_destroy_cb(string& code){
	m_log << verbose << "drwNativeWindow::on_destroy_cb(" << code << ")" << eol;
	m_on_destroy_cb = code;
	gtk_signal_connect(GTK_OBJECT(m_widget), "destroy", G_CALLBACK(callback), (gpointer)m_on_destroy_cb.c_str());
}

