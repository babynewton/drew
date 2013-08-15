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

drwGtkWindow::drwGtkWindow():drwGtkWidget(){
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
