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

#ifndef __DRW_TOKEN_OBJ_H__
#define __DRW_TOKEN_OBJ_H__

#include "log.h"

enum drwToken {
	DRW_TOKEN_NONE = 0,
	DRW_TOKEN_SYMBOL,
	DRW_TOKEN_FLOAT,
	DRW_TOKEN_INTEGER,
	DRW_TOKEN_STRING,
	DRW_TOKEN_CODE,
	DRW_TOKEN_BOOL,
	DRW_TOKEN_SEPARATOR,
	DRW_TOKEN_BEGINNING_OF_DICTIONARY,
	DRW_TOKEN_END_OF_DICTIONARY,
	DRW_TOKEN_BEGINNING_OF_LIST,
	DRW_TOKEN_END_OF_LIST,
	DRW_TOKEN_BEGINNING_OF_ARGUMENTS,
	DRW_TOKEN_END_OF_ARGUMENTS,
	DRW_TOKEN_END_OF_FILE,
	DRW_TOKEN_MAX
};

class drwTokenValue {
	friend class drwScanner;
	private:
		drwToken m_token;
		drwLog& m_log;
		string m_string;
		double m_float;
		int m_int;
		bool m_bool;

		const char* to_string(void);
	public:
		drwTokenValue();
		drwTokenValue(drwTokenValue& v);
		void operator = (drwTokenValue token);
		operator const char* (void);
		operator drwToken(void);
		string& symbol(void);
		string& text(void);
		string& code(void);
		double floating_number(void);
		int integer_number(void);
		bool boolean(void);
};

#endif //__DRW_TOKEN_OBJ_H__
