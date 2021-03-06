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
#include "box_parser.h"
#include "runtime.h"
#include "box.h"

drwBoxParser::drwBoxParser(drwBox* box):m_log(drwLog::instance()), m_box(box){
}

void drwBoxParser::onValue(const string name, const int value){
	if(name == "spacing"){
		m_box->spacing(value);
	} else if(name == "padding"){
		m_box->padding(value);
	} else {
		EXCEPT_UNRECOGNIZED(name);
	}
}

void drwBoxParser::onValue(const string name, const double value){
	EXCEPT_UNRECOGNIZED(name);
}

void drwBoxParser::onValue(const string name, const string value){
	EXCEPT_UNRECOGNIZED(name);
}

void drwBoxParser::onValue(const string name, const bool value){
	if(name == "homogeneous"){
		m_box->homogeneous(value);
	} else if(name == "expand"){
		m_box->expand(value);
	} else if(name == "fill"){
		m_box->fill(value);
	} else {
		EXCEPT_UNRECOGNIZED(name);
	}
}

void drwBoxParser::onScript(const string name, const string script, vector<string>& args){
	if(name == "_on_init"){
		drwRuntime* runtime = drwRuntime::instance();
		m_box->add_reference();
		runtime->run(m_box, script);
	} else {
		EXCEPT_UNRECOGNIZED(name);
	}
}

void drwBoxParser::onDictionaryOpen(const string name){
	EXCEPT_UNRECOGNIZED(name);
}

void drwBoxParser::onDictionaryClose(void){
	throw logic_error("Redundant }");
}

void drwBoxParser::onListOpen(const string name){
	EXCEPT_UNRECOGNIZED(name);
}

void drwBoxParser::onListClose(void){
	throw logic_error("Redundant ]");
}

void drwBoxParser::onEnd(void){
}

string drwBoxParser::profile(void){
	return "dml";
}

