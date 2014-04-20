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

#include <stdexcept>
#include <sstream>
#include "dml.h"
#include "dml_parser.h"
#include "engine.h"
#include "application_parser.h"
#include "window_parser.h"
#include "button_parser.h"
#include "box_parser.h"
#include "separator_parser.h"
#include "label_parser.h"

drwDml::drwDml(): m_log(drwLog::instance())
{
	m_callback_stack.push(new drwApplicationParser);
}
drwDml::~drwDml(){
	if(m_callback_stack.size() > 1) m_log << debug << "Unpared objects remain";
	while(!m_callback_stack.empty()){
		delete m_callback_stack.top();
		m_callback_stack.pop();
	}
	if(!m_widget_stack.empty()) m_log << debug << "Unparsed widget remain";
	while(!m_widget_stack.empty()){
		delete m_widget_stack.top();
		m_widget_stack.pop();
	}
}

void drwDml::onValue(const string name, const int value){
	drwDmlCallback* callback = m_callback_stack.top();
	callback->onValue(name, value);
}

void drwDml::onValue(const string name, const double value){
	drwDmlCallback* callback = m_callback_stack.top();
	callback->onValue(name, value);
}

void drwDml::onValue(const string name, const string value){
	drwDmlCallback* callback = m_callback_stack.top();
	callback->onValue(name, value);
}

void drwDml::onValue(const string name, const bool value){
	drwDmlCallback* callback = m_callback_stack.top();
	callback->onValue(name, value);
}

void drwDml::onScript(const string name, const string script, vector<string>& args){
	drwDmlCallback* callback = m_callback_stack.top();
	callback->onScript(name, script, args);
}

void drwDml::onDictionaryOpen(const string name){
	drwEngine* engine = drwEngine::instance();
	drwWidget* widget = NULL;
	drwDmlCallback* callback = NULL;
	if(name == "window") {
		widget = engine->window();
		callback = new drwWindowParser((drwWindow*)widget);
	}else if(name == "button") {
		widget = engine->button();
		callback = new drwButtonParser((drwButton*)widget);
	}else if(name == "label") {
		widget = engine->label();
		callback = new drwLabelParser((drwLabel*)widget);
	}else if(name == "hbox") {
		widget = engine->hbox();
		callback = new drwBoxParser((drwBox*)widget);
	}else if(name == "vbox") {
		widget = engine->vbox();
		callback = new drwBoxParser((drwBox*)widget);
	}else if(name == "hseparator") {
		widget = engine->hseparator();
		callback = new drwSeparatorParser(widget);
	}else if(name == "vbox") {
		widget = engine->vbox();
		callback = new drwSeparatorParser(widget);
	} else {
		EXCEPT_UNRECOGNIZED(name);
	}
	m_callback_stack.push(callback);
	m_widget_stack.push(widget);
}

void drwDml::onDictionaryClose(void){
	drwDmlCallback* cb = m_callback_stack.top();
	m_callback_stack.pop();
	delete cb;
	drwWidget* widget = m_widget_stack.top();
	m_widget_stack.pop();
	if(m_widget_stack.empty()){
		drwEngine* engine = drwEngine::instance();
		engine->add(widget);
	} else {
		drwWidget* parent = m_widget_stack.top();
		parent->add(widget);
	}
	delete widget;
}

void drwDml::onListOpen(const string name){
	drwDmlCallback* callback = m_callback_stack.top();
	callback->onListOpen(name);
}

void drwDml::onListClose(void){
	drwDmlCallback* callback = m_callback_stack.top();
	callback->onListClose();
}

void drwDml::onEnd(void){
}

string drwDml::profile(void){
	return "dml";
}
