#ifndef __DRW_GTK_WINDOW_H__
#define __DRW_GTK_WINDOW_H__

#include "../widget.h"
#include "log.h"
#include <gtk/gtk.h>

class drwGtkWidget: public drwWidget{
	protected:
		drwLog& m_log;
		GtkWidget* m_widget;
	public:
		drwGtkWidget();
		void add(drwWidget* widget);
		GtkWidget* widget(void);
};

#endif //__DRW_GTK_WINDOW_H__
