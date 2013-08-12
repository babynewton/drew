#ifndef __DRW_LOG_H__
#define __DRW_LOG_H__

#include <ostream>

using namespace std;

enum drwManipulator{
	verbose,
	debug,
	eol
};

enum drwLogLevel{
	DRW_LOG_LEVEL_NONE = 0,
	DRW_LOG_LEVEL_DEBUG,
	DRW_LOG_LEVEL_VERBOSE,
	DRW_LOG_LEVEL_MAX
};

class drwLog{
	private:
		bool m_onoff;
		drwLogLevel m_log_level;
	public:
		static void initialize(drwLogLevel level);
		static drwLog& instance(void);
		drwLog(drwLogLevel level);
		drwLog& operator <<(const char* v);
		drwLog& operator <<(const char v);
		drwLog& operator <<(const string& v);
		drwLog& operator <<(const int v);
		drwLog& operator <<(const unsigned int v);
		drwLog& operator <<(const double v);
		drwLog& operator <<(const drwManipulator v);
};

#endif //__DRW_LOG_H__
