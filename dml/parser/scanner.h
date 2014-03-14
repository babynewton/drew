/*
The MIT License (MIT)

Copyright (c) 2013 Newton Kim

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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
		drwToken scan(const int policy = DRW_SCAN_POLICY_NORMAL);
		string& symbol(void);
		string& text(void);
		string& code(void);
		double floating_number(void);
		int integer_number(void);
};

#endif //__DRW_SCANNER_H__
