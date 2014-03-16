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

#ifndef __DRW_DML_PARSER_H__
#define __DRW_DML_PARSER_H__

#include <string>
#include <map>
#include "scanner.h"
#include "log.h"

using namespace std;

#define EXCEPT_UNRECOGNIZED(name) {\
	stringstream ss;\
	ss << "Error: (" << __PRETTY_FUNCTION__ << ") Unrecognized symbol " << name;\
	throw logic_error(ss.str());\
}

class drwDmlCallback{
	public:
		virtual void onValue(const string name, const int value) = 0;
		virtual void onValue(const string name, const double value) = 0;
		virtual void onValue(const string name, const string value) = 0;
		virtual void onValue(const string name, const bool value) = 0;
		virtual void onScript(const string name, const string script) = 0;
		virtual void onDictionaryOpen(const string name) = 0;
		virtual void onDictionaryClose(void) = 0;
		virtual void onListOpen(const string name) = 0;
		virtual void onListClose(void) = 0;
		virtual void onEnd(void) = 0;
		virtual string profile(void) = 0;
};

class drwDmlParser{
	private:
		drwLog& m_log;
		map<string, int> m_script_symbols;

		void parse_a_header(drwScanner& scanner, drwDmlCallback* callback);
		void parse_a_list(drwScanner& scanner, drwDmlCallback* callback);
		void parse_a_dictionary(drwScanner& scanner, drwDmlCallback* callback, bool is_root = false);

	public:
		drwDmlParser();
		void parse(const string path, drwDmlCallback* callback);
	};

#endif //__DRW_DML_PARSER_H__
