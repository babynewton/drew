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
#include "window_parser.h"
#include "button_parser.h"

#include "window.h"
#include "engine.h"
#include "runtime.h"

drwWindowParser::drwWindowParser(drwWindow* window):m_log(drwLog::instance()), m_window(window){}

void drwWindowParser::onValue(const string name, const int value){
	if(name == "border"){
		m_window->border(value);
	} else {
		EXCEPT_UNRECOGNIZED(name);
	}
}

void drwWindowParser::onValue(const string name, const double value){
	EXCEPT_UNRECOGNIZED(name);
}

void drwWindowParser::onValue(const string name, const string value){
	if(name == "id"){
		drwEngine* engine = drwEngine::instance();
		engine->reserve(m_window, value);
	} else if(name == "title"){
		m_window->title(value);
	} else {
		EXCEPT_UNRECOGNIZED(name);
	}
}

void drwWindowParser::onValue(const string name, const bool value){
}

void drwWindowParser::onScript(const string name, const string script, vector<string>& args){
	if(name == "_before_destroy"){
		m_window->before_destroy_cb(script);
	} else if(name == "_on_destroy"){
		m_window->on_destroy_cb(script);
	} else if(name == "_on_init"){
		drwRuntime* runtime = drwRuntime::instance();
		m_window->add_reference();
		runtime->run(m_window, script);
	} else {
		EXCEPT_UNRECOGNIZED(name);
	}
}

void drwWindowParser::onDictionaryOpen(const string name){
	EXCEPT_UNRECOGNIZED(name);
}

void drwWindowParser::onDictionaryClose(void){
	throw logic_error("Redundant }");
}

void drwWindowParser::onListOpen(const string name){
	EXCEPT_UNRECOGNIZED(name);
}

void drwWindowParser::onListClose(void){
	throw logic_error("Redundant ]");
}

void drwWindowParser::onEnd(void){
}

string drwWindowParser::profile(void){
	return "dml";
}
