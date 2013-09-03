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

#include <stdexcept>
#include "../runtime.h"
#include "lua_gui.h"
#include "lua_log.h"
#include "lua_cout.h"


drwRuntime::drwRuntime():drwContext(){
	m_runner = luaL_newstate();
	luaL_openlibs(m_runner);
	lua_pushliteral(m_runner, "log");
	luaopen_log(m_runner);
	lua_pushliteral(m_runner, "gui");
	luaopen_gui(m_runner);
	lua_pushliteral(m_runner, "cout");
	luaopen_cout(m_runner);
}

void drwRuntime::execute(int nresults){
	if(lua_pcall(m_runner, 0, nresults, 0)) failed();
}

drwRuntime::~drwRuntime(){
	lua_close(m_runner);
}

drwThread* drwRuntime::thread(drwWidget* widget){
	return new drwThread(m_runner, widget);
}
