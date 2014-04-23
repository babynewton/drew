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

#include "gtk_engine.h"
#include "button.h"
#include "window.h"
#include <stdlib.h>
#include <sstream>
#include <stdexcept>
#include "runtime.h"
#include "dml/dml.h"
#include "gtk_factory.h"

static drwGtkEngine* s_current = NULL;

drwEngine* drwEngine::instance(void){
	if(!s_current) s_current = new drwGtkEngine;
	return s_current;
}

drwGtkEngine::drwGtkEngine():m_top(0), m_log(drwLog::instance())
{ }

void drwGtkEngine::initialize(int argc, char* argv[]){
	for(int i = 0 ; i < argc ; i++) m_log << verbose << argv[i] << eol;
	gtk_init(&argc, &argv);
}

void drwGtkEngine::add(drwWidget* widget){
	m_top = (GtkWidget*)(widget->handle());
}

void drwGtkEngine::run(void){
	gtk_main();
	gtk_exit(EXIT_SUCCESS);
}

void drwGtkEngine::quit(void){
	gtk_main_quit();
}

DRW_WIDGET_TYPE drwGtkEngine::type(const string& wid){
	GtkWidget* wgt = cache(wid);
	if(GTK_IS_WINDOW(wgt)) return DRW_WIDGET_TYPE_WINDOW;
	else if(GTK_IS_BUTTON(wgt)) return DRW_WIDGET_TYPE_BUTTON;
	else if(GTK_IS_LABEL(wgt)) return DRW_WIDGET_TYPE_LABEL;
	else if(GTK_IS_HBOX(wgt)) return DRW_WIDGET_TYPE_HBOX;
	else if(GTK_IS_VBOX(wgt)) return DRW_WIDGET_TYPE_VBOX;
	else if(GTK_IS_HSEPARATOR(wgt)) return DRW_WIDGET_TYPE_HSEPARATOR;
	else if(GTK_IS_VSEPARATOR(wgt)) return DRW_WIDGET_TYPE_VSEPARATOR;
	throw runtime_error("unrecognized type of widget");
}

GtkWidget* drwGtkEngine::cache(const string& wid){
	if(m_cache.find(wid) == m_cache.end()){
		stringstream ss;
		ss << wid << " not found";
		throw runtime_error(ss.str());
	}
	return m_cache[wid];
}

void drwGtkEngine::reserve(drwWidget* wgt, const string& id){
	cache((GtkWidget*)(wgt->handle()), id);
}

void drwGtkEngine::cache(GtkWidget* widget, const string& id){
	if(m_cache.find(id) != m_cache.end()){
		stringstream ss;
		ss << id << " already exist";
		throw runtime_error(ss.str());
	}
	m_log << verbose << "m_cache[" << id << "] << drwWidget*" << eol;
	m_cache[id] = widget;
}

drwWindow* drwGtkEngine::window(void){
	return drwWidgetFactory::window();
}

drwWindow* drwGtkEngine::window(const string& wid){
	return drwWidgetFactory::window(cache(wid));
}

drwButton* drwGtkEngine::button(void){
	return drwWidgetFactory::button();
}

drwButton* drwGtkEngine::button(const string& wid){
	return drwWidgetFactory::button(cache(wid));
}

drwHBox* drwGtkEngine::hbox(void){
	return drwWidgetFactory::hbox();
}

drwHBox* drwGtkEngine::hbox(const string& wid){
	return drwWidgetFactory::hbox(cache(wid));
}

drwVBox* drwGtkEngine::vbox(void){
	return drwWidgetFactory::vbox();
}

drwVBox* drwGtkEngine::vbox(const string& wid){
	return drwWidgetFactory::vbox(cache(wid));
}

drwHSeparator* drwGtkEngine::hseparator(void){
	return drwWidgetFactory::hseparator();
}

drwHSeparator* drwGtkEngine::hseparator(const string& wid){
	return drwWidgetFactory::hseparator(cache(wid));
}

drwVSeparator* drwGtkEngine::vseparator(void){
	return drwWidgetFactory::vseparator();
}

drwVSeparator* drwGtkEngine::vseparator(const string& wid){
	return drwWidgetFactory::vseparator(cache(wid));
}

drwLabel* drwGtkEngine::label(void){
	return drwWidgetFactory::label();
}

drwLabel* drwGtkEngine::label(const string& wid){
	return drwWidgetFactory::label(cache(wid));
}

void drwGtkEngine::parse(const string path, vector<string>& arguments){
	drwDmlParser parser;
	drwDml dml(arguments);
	parser.parse(path, &dml);
	if(m_top) gtk_widget_show_all(m_top);
}
