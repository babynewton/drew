#include <iostream>
#include "log.h"

drwLog::drwLog(bool onoff):m_onoff(onoff){
}

drwLog& drwLog::operator <<(const char* v){
	if(m_onoff) clog << v;
	return *this;
}

drwLog& drwLog::operator <<(const string& v){
	if(m_onoff) clog << v;
	return *this;
}

drwLog& drwLog::operator <<(const ostream& (*pf)(ostream&)){
	if(m_onoff) clog << pf;
	return * this;
}
