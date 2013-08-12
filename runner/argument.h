#ifndef __DRW_ARGUMENT_H__
#define __DRW_ARGUMENT_H__

#include <string>
#include "log.h"

using namespace std;

class drwArgument{
	private:
		drwLogLevel m_log_level;
		string m_path;
	public:
		drwArgument(int argc, char* argv[]);
		string& path(void);
		drwLogLevel log_level(void);
};

#endif //__DRW_ARGUMENT_H__
