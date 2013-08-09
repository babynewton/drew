#ifndef __DRW_DML_PARSER_H__
#define __DRW_DML_PARSER_H__

#include <string>
#include "engine.h"

using namespace std;

class drwDmlParser{
	public:
		drwEngine* parse(const string path);
};

#endif //__DRW_DML_PARSER_H__
