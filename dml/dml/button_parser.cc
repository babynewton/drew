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


drwButtonParser::drwButtonParser(drwEngine* engine):m_log(drwLog::instance()), m_engine(engine), m_button(NULL){}

void drwButtonParser::onValue(const string name, const int value){
	EXCEPT_UNRECOGNIZED(name);
}

void drwButtonParser::onValue(const string name, const double value){
	EXCEPT_UNRECOGNIZED(name);
}

void drwButtonParser::onValue(const string name, const string value){
	if(name == "id"){
		m_button->id(value);
		m_engine->cache(m_button);
	} else if(name == "label"){
		m_button->label(value);
	} else {
		EXCEPT_UNRECOGNIZED(name);
	}
}

void drwButtonParser::onValue(const string name, const bool value){
	EXCEPT_UNRECOGNIZED(name);
}

void drwButtonParser::onScript(const string name, const string script){
	if(name == "_on_click"){
		m_button->click_cb(script);
	} else {
		EXCEPT_UNRECOGNIZED(name);
	}
}

void drwButtonParser::onStructureOpen(const string name){
	EXCEPT_UNRECOGNIZED(name);
}

void drwButtonParser::onStructureClose(void){
	throw logic_error("Error: Redundant closing bracked");
}

void drwButtonParser::onEnd(void){
}

void drwButtonParser::set_button(drwButton* button){
	m_button = button;
}
