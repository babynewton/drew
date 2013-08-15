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
