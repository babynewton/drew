#ifndef __DRW_DML_PARSER_H__
#define __DRW_DML_PARSER_H__

#include <string>
#include "log.h"
#include "engine.h"

using namespace std;

class drwDmlParser{
	private:
		drwLog m_log;

	public:
		drwDmlParser(const bool onoff);
		drwEngine* parse(const string path);
};

#endif //__DRW_DML_PARSER_H__
