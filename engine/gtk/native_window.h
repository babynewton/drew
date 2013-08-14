#ifndef __DRW_NATIVE_WINDOW_H__
#define __DRW_NATIVE_WINDOW_H__

#include "../window.h"
#include "log.h"
#include <gtk/gtk.h>

class drwNativeWindow : public drwWindow{
	private:
		drwLog& m_log;
		GtkWidget* m_widget;
		string m_before_destroy_cb;
		string m_on_destroy_cb;
		static gboolean callback_with_event(GtkWidget* widget, GdkEvent* event, gpointer data);
		static void callback(GtkWidget* widget, gpointer data);
	public:
		drwNativeWindow();
		void add(drwButton* button);
		void border(int border);
		void before_destroy_cb(string& cb);
		void on_destroy_cb(string& cb);
};

#endif //__DRW_NATIVE_WINDOW_H__
