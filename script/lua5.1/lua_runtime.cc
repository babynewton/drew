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

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <stdexcept>
#include "lua_runtime.h"
#include "lua_gui.h"
#include "lua_log.h"
#include "lua_cout.h"
#include "widget.h"
#include "lua_dthread.h"

static drwLuaRuntime* s_runtime = NULL;

drwRuntime* drwRuntime::instance(void){
	if(!s_runtime) s_runtime = new drwLuaRuntime;
	return s_runtime;
}

drwLuaRuntime::drwLuaRuntime():m_log(drwLog::instance()){
	m_runner = luaL_newstate();
	luaL_openlibs(m_runner);
	lua_pushliteral(m_runner, "log");
	luaopen_log(m_runner);
	lua_pushliteral(m_runner, "gui");
	luaopen_gui(m_runner);
	lua_pushliteral(m_runner, "cout");
	luaopen_cout(m_runner);
}

drwLuaRuntime::~drwLuaRuntime(){
	lua_close(m_runner);
}

void drwLuaRuntime::failed(void){
	const char* err = lua_tostring(m_runner, -1);
	m_log << debug << err << eol;
	throw runtime_error(err);
}

void drwLuaRuntime::initialize(const string& code){
	if (luaL_loadstring(m_runner, code.c_str())) failed();
	if(lua_pcall(m_runner, 0, 0, 0)) failed();
}

bool drwLuaRuntime::run(drwWidget* widget, const unsigned long index){
	string code = m_codes[widget->uid()][index];
	drwLuaThread thread(m_runner, widget);
	return thread.run(code.c_str());
}

const unsigned long drwLuaRuntime::script(unsigned long uid, const string& code){
	m_log << debug << "m_codes[" << uid << "] = " << code << eol;
	m_codes[uid].push_back(code);
	return m_codes[uid].size() - 1;
}
