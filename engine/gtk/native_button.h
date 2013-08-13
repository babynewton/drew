#ifndef __DRW_NATIVE_BUTTON_H__
#define __DRW_NATIVE_BUTTON_H__

#include "../button.h"
#include "log.h"
#include <gtk/gtk.h>

class drwNativeButton : public drwButton {
	private:
		drwLog& m_log;
		GtkWidget* m_widget;
		string m_click_cb;
		static gboolean callback(GtkWidget* widget, gpointer data);
	public:
		drwNativeButton();
		void label(string& lbl);
		void click_cb(string& code);
		GtkWidget* widget(void);
};

#endif //__DRW_NATIVE_BUTTON_H__
