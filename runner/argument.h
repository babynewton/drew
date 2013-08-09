#ifndef __DRW_ARGUMENT_H__
#define __DRW_ARGUMENT_H__

#include <string>

using namespace std;

class drwArgument{
	private:
		string m_path;
	public:
		drwArgument(int argc, char* argv[]);
		string& path(void);
};

#endif //__DRW_ARGUMENT_H__
