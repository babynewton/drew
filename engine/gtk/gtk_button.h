#ifndef __DRW_NATIVE_BUTTON_H__
#define __DRW_NATIVE_BUTTON_H__

#include "../button.h"
#include "gtk_widget.h"
#include "log.h"
#include <gtk/gtk.h>

class drwGtkButton : public drwButton, drwGtkWidget {
	private:
		string m_click_cb;
		static void callback(GtkWidget* widget, gpointer data);
	public:
		drwGtkButton();
		void label(string& lbl);
		void click_cb(string& code);
		drwWidget* to_widget(void);
};

#endif //__DRW_NATIVE_BUTTON_H__
