#ifndef __DRW_SCANNER_H__
#define __DRW_SCANNER_H__

#include <string>
#include "log.h"

using namespace std;

enum drwToken {
	DRW_TOKEN_NONE = 0,
	DRW_TOKEN_SYMBOL,
	DRW_TOKEN_FLOAT,
	DRW_TOKEN_INTEGER,
	DRW_TOKEN_STRING,
	DRW_TOKEN_CODE,
	DRW_TOKEN_SEPARATOR,
	DRW_TOKEN_BEGINNING_OF_DICTIONARY,
	DRW_TOKEN_END_OF_DICTIONARY,
	DRW_TOKEN_BEGINNING_OF_LIST,
	DRW_TOKEN_END_OF_LIST,
	DRW_TOKEN_MAX
};

#define DRW_SCAN_POLICY_NORMAL 0x0
#define DRW_SCAN_POLICY_DICTIONARY_AS_CODE 0x1

class drwScanner {
	private:
		drwLog& m_log;
		char* m_begin;
		char* m_end;
		char* m_pointer;
		string m_string;
		drwToken m_token;
		double m_float;
		int m_int;
		unsigned int m_line;
		string m_path;
		drwToken scan_a_string(char endc);
		drwToken scan_a_symbol(void);
		void scan_eol(void);
		drwToken scan_a_number(void);
		void skip_a_line(void);

	public:
		drwScanner(const string& path);
		bool eof(void);
		drwToken scan(unsigned int policy = DRW_SCAN_POLICY_NORMAL);
		string& symbol(void);
		string& code(void);
		double floating_number(void);
		int integer_number(void);
};

#endif //__DRW_SCANNER_H__
