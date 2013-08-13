#ifndef __DRW_SCANNER_H__
#define __DRW_SCANNER_H__

#include <string>
#include "log.h"
#include "token.h"

using namespace std;

#define DRW_SCAN_POLICY_NORMAL 0x0
#define DRW_SCAN_POLICY_DICTIONARY_AS_CODE 0x1

class drwScanner {
	private:
		drwLog& m_log;
		char* m_begin;
		char* m_end;
		char* m_pointer;
		string m_string;
		drwTokenValue m_token;
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
		~drwScanner();
		bool eof(void);
		drwToken scan(unsigned int policy = DRW_SCAN_POLICY_NORMAL);
		string& symbol(void);
		string& text(void);
		string& code(void);
		double floating_number(void);
		int integer_number(void);
};

#endif //__DRW_SCANNER_H__
