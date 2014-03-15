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

#include "dml.h"
#include "parser/dml_parser.h"

drwDml::drwDml(drwEngine* engine):
		m_log(drwLog::instance()),
		m_engine(engine),
		m_application(engine),
		m_window(engine),
		m_button(engine),
		m_window_widget(NULL),
		m_button_widget(NULL)
{
	m_stack.push(&m_application);
}

const char* script_symbols[] ={
	"_on_init",
	"_before_destroy",
	"_on_destroy",
	"_on_click",
	NULL
};

void drwDml::parse(const string path){
	m_log << debug << "drwDmlPaser parses " << path << eol;
	drwDmlParser parser(m_engine);
	parser.set_script_symbols(script_symbols);
	parser.parse(path, this);
}

void drwDml::onValue(const string name, const int value){
	drwDmlCallback* callback = m_stack.top();
	callback->onValue(name, value);
}

void drwDml::onValue(const string name, const double value){
	drwDmlCallback* callback = m_stack.top();
	callback->onValue(name, value);
}

void drwDml::onValue(const string name, const string value){
	drwDmlCallback* callback = m_stack.top();
	callback->onValue(name, value);
}

void drwDml::onScript(const string name, const string script){
	drwDmlCallback* callback = m_stack.top();
	callback->onValue(name, script);
}

void drwDml::onStructureOpen(const string name){
	if(name == "window") {
		m_window_widget = new drwWindow;
		m_window.set_window(m_window_widget);
		m_stack.push(&m_window);
	}else if(name == "button") {
		m_button_widget = new drwButton;
		m_button.set_button(m_button_widget);
		m_stack.push(&m_button);
	}
}

void drwDml::onStructureClose(void){
	drwDmlCallback* callback = m_stack.top();
	m_stack.pop();
	if(callback == &m_window){
		if(m_window_widget) m_engine->top((drwWidget*)m_window_widget);
	}
}


