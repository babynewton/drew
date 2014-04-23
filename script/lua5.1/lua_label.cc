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

#include "lua_label.h"
#include "lua_widget.h"
#include "log.h"

#define DRW_LUA_LABEL "drwLuaLabel"

int lua_label_new(lua_State* L, drwLabel* label){
	drwLog& log = drwLog::instance();
	log << verbose << "lua_label_as_this" << eol;
	drwLabel** lbl = (drwLabel**)lua_newuserdata(L, sizeof(drwLabel*));
	*lbl = label;
	luaL_getmetatable(L, DRW_LUA_LABEL);
	lua_setmetatable(L, -2);
	return 1;
}

int lua_label_as_this(lua_State* L, drwLabel* label){
	drwLog& log = drwLog::instance();
	log << verbose << "lua_label_as_this" << eol;
	drwLabel** lbl = (drwLabel**)lua_newuserdata(L, sizeof(drwLabel*));
	luaL_getmetatable(L, DRW_LUA_LABEL);
	lua_setmetatable(L, -2);
	*lbl = label;
	lua_setglobal(L, "this");
	return 0;
}

static int lua_label_label(lua_State* L){
	int args = lua_gettop(L);
	int ret = 0;
	if(args < 1) { //ERROR
		luaL_error(L, "No label object in the stack");
		return 1;
	}
	if(!lua_isuserdata(L, 1)){
		luaL_error(L, "The label object is not an user data");
		return 1;
	}
	drwLabel* lbl = *(drwLabel**)lua_touserdata(L, 1);
	if(args == 1) {
		lua_pushstring(L, lbl->text().c_str());
		ret = 1;
	} else {
		if(!lua_isstring(L, 2)){
			luaL_error(L, "The argument to the label is not a string");
			return 1;
		}
		lbl->text(lua_tostring(L, 2));
		ret = 0;
	}
	return ret;
}

static int lua_label_gc(lua_State* L){
	int args = lua_gettop(L);
	if(args < 1) { //ERROR
		luaL_error(L, "No label object in the stack");
		return 1;
	}
	if(!lua_isuserdata(L, 1)){
		luaL_error(L, "The label object is not an user data");
		return 1;
	}
	drwLabel* lbl = *(drwLabel**)lua_touserdata(L, 1);
	delete lbl;
	return 0;
}

static const luaL_Reg lbllib[] = {
	{"label", lua_label_label},
	{"show", lua_widget_show},
	{"hide", lua_widget_hide},
	{"__gc", lua_label_gc},
	{NULL, NULL}
};

void lua_label_init(lua_State* L){
	luaL_newmetatable(L, DRW_LUA_LABEL);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_register(L, NULL, lbllib);
}
