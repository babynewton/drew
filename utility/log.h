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

#ifndef __DRW_LOG_H__
#define __DRW_LOG_H__

#include <ostream>

using namespace std;

enum drwManipulator{
	verbose,
	debug,
	eol,
	hexa,
	deca,
	octa
};

enum drwLogLevel{
	DRW_LOG_LEVEL_NONE = 0,
	DRW_LOG_LEVEL_DEBUG,
	DRW_LOG_LEVEL_VERBOSE,
	DRW_LOG_LEVEL_MAX
};

class drwLog{
	private:
		bool m_onoff;
		drwLogLevel m_log_level;
	public:
		static void initialize(drwLogLevel level);
		static drwLog& instance(void);
		drwLog(drwLogLevel level);
		drwLog& operator <<(const char* v);
		drwLog& operator <<(const char v);
		drwLog& operator <<(const string& v);
		drwLog& operator <<(const int v);
		drwLog& operator <<(const unsigned int v);
		drwLog& operator <<(const double v);
		drwLog& operator <<(const bool v);
		drwLog& operator <<(const drwManipulator v);
};

#endif //__DRW_LOG_H__
