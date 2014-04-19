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
	//TODO:never again
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

drwButton* drwGtkEngine::button(void){
	return drwWidgetFactory::button();
}

drwHBox* drwGtkEngine::hbox(void){
	return drwWidgetFactory::hbox();
}

drwWindow* drwGtkEngine::window(const string& wid){
	return drwWidgetFactory::window(cache(wid));
}

drwButton* drwGtkEngine::button(const string& wid){
	return drwWidgetFactory::button(cache(wid));
}

drwHBox* drwGtkEngine::hbox(const string& wid){
	return drwWidgetFactory::hbox(cache(wid));
}

void drwGtkEngine::parse(const string path){
	drwDmlParser parser;
	drwDml dml;
	parser.parse(path, &dml);
}
