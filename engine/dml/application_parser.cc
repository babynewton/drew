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
#include "../../config.h"
#include "application_parser.h"

drwApplicationParser::drwApplicationParser(drwEngine* engine):m_log(drwLog::instance()), m_engine(engine){
}

void drwApplicationParser::onValue(const string name, const int value){
	EXCEPT_UNRECOGNIZED(name);
}

void drwApplicationParser::onValue(const string name, const double value){
	EXCEPT_UNRECOGNIZED(name);
}

void drwApplicationParser::onValue(const string name, const string value){
	EXCEPT_UNRECOGNIZED(name);
}

void drwApplicationParser::onValue(const string name, const bool value){
	EXCEPT_UNRECOGNIZED(name);
}

void drwApplicationParser::onScript(const string name, const string script){
	if(name == "_on_init") {
		m_engine->on_init_cb(script);
	} else {
		EXCEPT_UNRECOGNIZED(name);
	}
}

void drwApplicationParser::onStructureOpen(const string name){
	EXCEPT_UNRECOGNIZED(name);
}

void drwApplicationParser::onStructureClose(void){
	throw logic_error("Redundant }");
}

void drwApplicationParser::onListOpen(const string name){
	EXCEPT_UNRECOGNIZED(name);
}

void drwApplicationParser::onListClose(void){
	throw logic_error("Redundant ]");
}

void drwApplicationParser::onEnd(void){
}

string drwApplicationParser::profile(void){
	return "dml";
}
