#ifndef __DRW_SCANNER_H__
#define __DRW_SCANNER_H__

#include "log.h"

#define DRW_SCANNER_BUFFER_SIZE 512
enum drwToken {
	DRW_TOKEN_NONE = 0,
	DRW_TOKEN_TAG,
	DRW_TOKEN_FLOAT,
	DRW_TOKEN_BEGINNING_OF_DICTIONARY,
	DRW_TOKEN_END_OF_DICTIONARY,
	DRW_TOKEN_BEGINNING_OF_LIST,
	DRW_TOKEN_END_OF_LIST,
	DRW_TOKEN_MAX
};

class drwScanner {
	private:
		drwLog& m_log;
		char* m_begin;
		char* m_end;
		char* m_pointer;
		char m_string[DRW_SCANNER_BUFFER_SIZE];
		drwToken m_token;
		double m_float;
		const char* token_string(void);

	public:
		drwScanner(const string& path, drwLog& log);
		bool eof(void);
		drwToken scan(void);
		const char* tag(void);
		double floating_number(void);
};

#endif //__DRW_SCANNER_H__
