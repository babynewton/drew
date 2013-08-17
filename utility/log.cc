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

#include <iostream>
#include <stdexcept>
#include "log.h"

drwLog::drwLog(drwLogLevel level):
	m_onoff(false),
	m_log_level(level){}

drwLog& drwLog::operator <<(const char* v){
	if(m_onoff) clog << v;
	return *this;
}

drwLog& drwLog::operator <<(const char v){
	if(m_onoff) clog << v;
	return *this;
}

drwLog& drwLog::operator <<(const string& v){
	if(m_onoff) clog << v;
	return *this;
}

drwLog& drwLog::operator <<(const int v){
	if(m_onoff) clog << v;
	return *this;
}

drwLog& drwLog::operator <<(const unsigned int v){
	if(m_onoff) clog << v;
	return *this;
}

drwLog& drwLog::operator <<(const double v){
	if(m_onoff) clog << v;
	return *this;
}

drwLog& drwLog::operator <<(const drwManipulator v){
	switch (v){
		case debug:
			if(m_log_level >= DRW_LOG_LEVEL_DEBUG) m_onoff = true;
			if(m_onoff) clog << "[debug] ";
			break;
		case verbose:
			if(m_log_level == DRW_LOG_LEVEL_VERBOSE) m_onoff = true;
			if(m_onoff) clog << "[verbose] ";
			break;
		case eol:
			if(m_onoff) clog << endl;
			m_onoff = false;
			break;
	}
	return *this;
}


//=============================================================

drwLog* s_logger = NULL;

void drwLog::initialize(const drwLogLevel level){
	if(s_logger) *s_logger << debug << "drwLog has been already initialized";
	s_logger = new drwLog(level);
}

drwLog& drwLog::instance(void){
	if(!s_logger) throw runtime_error("The client tried to instantiated drwLoger before the initialization");
	return *s_logger;
}

