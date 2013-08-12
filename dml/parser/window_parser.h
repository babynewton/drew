#ifndef __DRW_WINDOW_PARSER_H__
#define __DRW_WINDOW_PARSER_H__

#include "log.h"
#include "scanner.h"
#include "engine.h"

class drwWindowParser{
	private:
		drwLog& m_log;
	public:
		drwWindowParser();
		drwWindow* parse(drwScanner& scanner);
};

#endif //__DRW_WINDOW_PARSER_H__
