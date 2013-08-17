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

#include "lua_log.h"
#include "log.h"

static int log_verbose(lua_State* L){
	drwLog& log = drwLog::instance();
	log << verbose;
	while(lua_gettop(L)) {
		log << lua_tostring(L, -1);
		lua_pop(L, 1);
	}
	log << eol;
	return 0;
}

static int log_debug(lua_State* L){
	drwLog& log = drwLog::instance();
	log << debug;
	while(lua_gettop(L)) {
		log << lua_tostring(L, -1);
		lua_pop(L, 1);
	}
	log << eol;
	return 0;
}

static const luaL_Reg loglib[] = {
	{"verbose", log_verbose},
	{"debug", log_debug},
	{NULL, NULL}
};

LUALIB_API int luaopen_log(lua_State* L){
	luaL_register(L, "log", loglib);
	 return 1;
}
