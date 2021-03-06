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
#include "button_parser.h"
#include "engine.h"
#include "runtime.h"


drwButtonParser::drwButtonParser(drwButton* button):m_log(drwLog::instance()), m_button(button){}

void drwButtonParser::onValue(const string name, const int value){
	EXCEPT_UNRECOGNIZED(name);
}

void drwButtonParser::onValue(const string name, const double value){
	EXCEPT_UNRECOGNIZED(name);
}

void drwButtonParser::onValue(const string name, const string value){
	if(name == "id"){
		drwEngine* engine = drwEngine::instance();
		engine->reserve(m_button, value);
	} else if(name == "label"){
		m_button->label(value);
	} else {
		EXCEPT_UNRECOGNIZED(name);
	}
}

void drwButtonParser::onValue(const string name, const bool value){
	EXCEPT_UNRECOGNIZED(name);
}

void drwButtonParser::onScript(const string name, const string script, vector<string>& args){
	if(name == "_on_click"){
		m_button->click_cb(script);
	} else if(name == "_on_init"){
		drwRuntime* runtime = drwRuntime::instance();
		m_button->add_reference();
		runtime->run(m_button, script);
	} else {
		EXCEPT_UNRECOGNIZED(name);
	}
}

void drwButtonParser::onDictionaryOpen(const string name){
	EXCEPT_UNRECOGNIZED(name);
}

void drwButtonParser::onDictionaryClose(void){
	throw logic_error("Redundant }");
}

void drwButtonParser::onListOpen(const string name){
	EXCEPT_UNRECOGNIZED(name);
}

void drwButtonParser::onListClose(void){
	throw logic_error("Redundant ]");
}

void drwButtonParser::onEnd(void){
}

string drwButtonParser::profile(void){
	return "dml";
}
