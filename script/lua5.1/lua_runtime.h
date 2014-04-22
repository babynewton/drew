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

#ifndef __DRW_LUA_RUNTIME_H__
#define __DRW_LUA_RUNTIME_H__

#include <map>
#include <vector>
#include <string>

extern "C" {
#include <lua.h>
}

#include "../runtime.h"
#include "log.h"

class drwLuaRuntime : public drwRuntime{
	friend class drwLuaThread;
	private:
		map<unsigned long, vector<string> > m_codes;
		drwLog& m_log;
		lua_State* m_runner;
		void failed(void);

	public:
		drwLuaRuntime();
		~drwLuaRuntime();
		void initialize(const string& code, vector<string>& arguments);
		bool run(drwWidget* button, const unsigned long index);
		bool run(drwWidget* button, const string& code);
		const unsigned long script(unsigned long uid, const string& code);
};

#endif //__DRW_LUA_RUNTIME_H__
