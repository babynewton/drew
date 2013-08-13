#ifndef __DRW_DML_PARSER_H__
#define __DRW_DML_PARSER_H__

#include <string>
#include "log.h"
#include "engine.h"
#include "scanner.h"

using namespace std;

class drwDmlParser{
	private:
		drwLog& m_log;

	public:
		drwDmlParser();
		void parse(drwEngine* engine, drwScanner& scanner);
};

#endif //__DRW_DML_PARSER_H__
