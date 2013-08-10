#include <iostream>
#include "log.h"

drwLog::drwLog(bool onoff):
	m_line_onoff(false),
	m_onoff(onoff){}

drwLog& drwLog::operator <<(const char* v){
	if(m_onoff || m_line_onoff) clog << v;
	return *this;
}

drwLog& drwLog::operator <<(const string& v){
	if(m_onoff || m_line_onoff) clog << v;
	return *this;
}

drwLog& drwLog::operator <<(const drwManipulator v){
	switch (v){
		case error:
			m_line_onoff = true;
			clog << "[error] ";
			break;
		case verbose:
			if(m_onoff) clog << "[verbose] ";
			break;
		case eol:
			if(m_onoff) clog << endl;
			m_line_onoff = false;
			break;
	}
	return *this;
}

