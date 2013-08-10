#ifndef __DRW_SCANNER_H__
#define __DRW_SCANNER_H__

#include "log.h"

enum drwToken {
	DRW_TOKEN_NONE = 0,
	DRW_TOKEN_TAG,
	DRW_TOKEN_INTEGER,
	DRW_TOKEN_FLOAT,
	DRW_TOKEN_STRING,
	DRW_TOKEN_DICTIONARY,
	DRW_TOKEN_LIST
};

class drwScanner {
	private:
		drwLog& m_log;
	public:
		drwScanner(drwScanner& scanner);
		drwScanner(const string& path, drwLog& log);
		bool eof(void);
		drwToken scan(void);
		const char* tag(void);
};

#endif //__DRW_SCANNER_H__
