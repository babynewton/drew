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

