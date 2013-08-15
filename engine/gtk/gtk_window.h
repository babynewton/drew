#ifndef __DRW_NATIVE_WINDOW_H__
#define __DRW_NATIVE_WINDOW_H__

#include "../window.h"
#include "log.h"
#include "gtk_widget.h"
#include <gtk/gtk.h>

class drwGtkWindow : public drwGtkWidget, drwWindow{
	private:
		string m_before_destroy_cb;
		string m_on_destroy_cb;
		static gboolean callback_with_event(GtkWidget* widget, GdkEvent* event, gpointer data);
		static void callback(GtkWidget* widget, gpointer data);
	public:
		drwGtkWindow();
		void border(int border);
		void before_destroy_cb(string& cb);
		void on_destroy_cb(string& cb);
		drwWidget* to_widget(void);
};

#endif //__DRW_NATIVE_WINDOW_H__
