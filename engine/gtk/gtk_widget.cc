/*
The MIT License (MIT)

Copyright (c) 2013 Newton Kim

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <gtk/gtk.h>
#include <stdexcept>
#include "widget.h"

const char* s_type_str[] = {
	"unknown",
	"window",
	"button",
	"label",	
	"hbox",
	"vbox",
	"hseparator",
	"vseparator"
};

drwWidget::drwWidget() :
	m_type(DRW_WIDGET_TYPE_UNKNOWN),
	m_handle(0),
	m_log(drwLog::instance()),
	m_reference(1)
{
}

drwWidget::drwWidget(drwWidget* widget) :
	m_type(widget->m_type),
	m_handle(widget->m_handle),
	m_log(drwLog::instance()),
	m_reference(1)
{
}

drwWidget::~drwWidget(){ }

unsigned long drwWidget::uid(void){
	return (unsigned long)m_handle;
}

void drwWidget::add(drwWidget* widget){
	throw runtime_error("Invalid opation");
}

const DRW_WIDGET_TYPE drwWidget::type(void){
	return m_type;
}

const void* drwWidget::handle(void){
	return m_handle;
}

const char* drwWidget::type_str(void){
	return s_type_str[m_type];
}

void drwWidget::show(const bool all){
	if(all) gtk_widget_show_all(GTK_WIDGET(m_handle));
	else gtk_widget_show(GTK_WIDGET(m_handle));
}

void drwWidget::hide(const bool all){
	if(all) gtk_widget_hide(GTK_WIDGET(m_handle));
	else gtk_widget_hide(GTK_WIDGET(m_handle));
}

void drwWidget::add_reference(void){
	m_reference++;
}

void drwWidget::release(void){
	if(m_reference > 1) m_reference--;
	else delete this;
}

