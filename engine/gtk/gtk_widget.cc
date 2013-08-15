#include <string>
#include <iostream>
#include "gtk_widget.h"
#include "gtk_button.h"
#include "runtime.h"

using namespace std;

drwGtkWidget::drwGtkWidget():m_log(drwLog::instance()){ }

void drwGtkWidget::add(drwWidget* widget){
	drwGtkWidget* wgt = (drwGtkWidget*) widget;
	gtk_container_add(GTK_CONTAINER(m_widget), wgt->widget());
}

GtkWidget* drwGtkWidget::widget(void){
	return m_widget;
}
