#ifndef __DRW_DML_H__
#define __DRW_DML_H__

#include <string>
#include "log.h"
#include "engine.h"

using namespace std;

class drwDml{
	private:
		drwLog m_log;

	public:
		drwDml(const bool onoff);
		drwEngine* parse(const string path);
};

#endif //__DRW_DML_H__
