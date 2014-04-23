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

#include "lua_separator.h"
#include "lua_widget.h"
#include "log.h"

#define DRW_LUA_SEPARATOR "drwLuaSeparator"

int lua_hseparator_new(lua_State* L, drwHSeparator* hseparator){
	drwLog& log = drwLog::instance();
	log << verbose << "lua_hseparator_new" << eol;
	drwHSeparator** separator = (drwHSeparator**)lua_newuserdata(L, sizeof(drwHSeparator*));
	*separator = hseparator;
	luaL_getmetatable(L, DRW_LUA_SEPARATOR);
	lua_setmetatable(L, -2);
	return 1;
}

int lua_hseparator_as_this(lua_State* L, drwHSeparator* hseparator){
	drwLog& log = drwLog::instance();
	log << verbose << "lua_hseparator_as_this" << eol;
	drwHSeparator** separator = (drwHSeparator**)lua_newuserdata(L, sizeof(drwHSeparator*));
	luaL_getmetatable(L, DRW_LUA_SEPARATOR);
	lua_setmetatable(L, -2);
	*separator = hseparator;
	lua_setglobal(L, "this");
	return 0;
}

int lua_vseparator_new(lua_State* L, drwVSeparator* vseparator){
	drwLog& log = drwLog::instance();
	log << verbose << "lua_vseparator_new" << eol;
	drwVSeparator** separator = (drwVSeparator**)lua_newuserdata(L, sizeof(drwVSeparator*));
	*separator = vseparator;
	luaL_getmetatable(L, DRW_LUA_SEPARATOR);
	lua_setmetatable(L, -2);
	return 1;
}

int lua_vseparator_as_this(lua_State* L, drwVSeparator* vseparator){
	drwLog& log = drwLog::instance();
	log << verbose << "lua_vseparator_as_this" << eol;
	drwVSeparator** separator = (drwVSeparator**)lua_newuserdata(L, sizeof(drwVSeparator*));
	luaL_getmetatable(L, DRW_LUA_SEPARATOR);
	lua_setmetatable(L, -2);
	*separator = vseparator;
	lua_setglobal(L, "this");
	return 0;
}

static const luaL_Reg separatorlib[] = {
	{"show", lua_widget_show},
	{"hide", lua_widget_hide},
	{"__gc", lua_widget_gc},
	{NULL, NULL}
};

void lua_separator_init(lua_State* L){
	luaL_newmetatable(L, DRW_LUA_SEPARATOR);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_register(L, NULL, separatorlib);
}
