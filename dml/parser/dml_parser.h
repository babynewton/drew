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
#include "log.h"
#include "engine.h"

using namespace std;

class drwDmlCallback{
	public:
		virtual void onValue(const string name, const int value) = 0;
		virtual void onValue(const string name, const double value) = 0;
		virtual void onValue(const string name, const string value) = 0;
		virtual void onScript(const string name, const string script) = 0;
		virtual void onStructureOpen(const string name) = 0;
		virtual void onStructureClose(void) = 0;
};

class drwDmlParser{
	private:
		drwLog& m_log;
		drwEngine* m_engine;
		map<string, int> m_script_symbols;

	public:
		drwDmlParser(drwEngine* engine);
		void set_script_symbols(const char* script_symbols[]);
		void parse(const string path, drwDmlCallback* callback);
};

#endif //__DRW_DML_PARSER_H__
