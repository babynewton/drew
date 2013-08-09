#ifndef __DRW_LOG_H__
#define __DRW_LOG_H__

#include <ostream>

using namespace std;

class drwLog{
	private:
		bool m_onoff;
	public:
		drwLog(bool onoff);
		drwLog& operator <<(const char* v);
		drwLog& operator <<(const string& v);
		drwLog& operator <<(const ostream& (*pf)(ostream&));
};

#endif //__DRW_LOG_H__
