#ifndef __DRW_BUTTON_PARSER_H__
#define __DRW_BUTTON_PARSER_H__

#include "log.h"
#include "scanner.h"
#include "button.h"

class drwButtonParser{
	private:
		drwLog& m_log;
	public:
		drwButtonParser();
		drwButton* parse(drwScanner& scanner);
};

#endif //__DRW_BUTTON_PARSER_H__
