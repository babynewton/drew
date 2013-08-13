#include "native_button.h"
#include "runtime.h"

gboolean drwNativeButton::callback(GtkWidget* widget, gpointer data){
	drwRuntime rt;
	try{
		rt.run((const char*) data);
	}catch(exception& e){
	}
	return TRUE;
}

drwNativeButton::drwNativeButton():m_log(drwLog::instance()), m_widget(gtk_button_new()){
	gtk_widget_show(m_widget);
}

void drwNativeButton::label(string& lbl){
	gtk_button_set_label(GTK_BUTTON(m_widget), lbl.c_str());
}

void drwNativeButton::click_cb(string& code){
	m_log << verbose << "drwNativeButton::click_cb(" << code << ")" << eol;
	m_click_cb = code;
	gtk_signal_connect(GTK_OBJECT(m_widget), "clicked", G_CALLBACK(callback), (gpointer)m_click_cb.c_str());
}

GtkWidget* drwNativeButton::widget(void){
	m_log << verbose << "(GtkWidget*) drwNativeButton" << eol;
	return m_widget;
}
