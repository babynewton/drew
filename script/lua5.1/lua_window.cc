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

#include "lua_window.h"
#include "lua_widget.h"

#define DRW_LUA_WINDOW "drwLuaWindow"

int lua_window_new(lua_State* L, drwWindow* window){
	drwWindow** wnd = (drwWindow**)lua_newuserdata(L, sizeof(drwWindow*));
	*wnd = window;
	luaL_getmetatable(L, DRW_LUA_WINDOW);
	lua_setmetatable(L, -2);
	return 1;
}

int lua_window_as_this(lua_State* L, drwWindow* window){
	drwWindow** wnd = (drwWindow**)lua_newuserdata(L, sizeof(drwWindow*));
	luaL_getmetatable(L, DRW_LUA_WINDOW);
	lua_setmetatable(L, -2);
	*wnd = window;
	lua_setglobal(L, "this");
	return 0;
}

static int lua_window_title(lua_State* L){
	int args = lua_gettop(L);
	int ret = 0;
	if(args < 1) { //ERROR
		luaL_error(L, "No window object in the stack");
		return 1;
	}
	if(!lua_isuserdata(L, 1)){
		luaL_error(L, "The window object is not an user data");
		return 1;
	}
	drwWindow* wnd = *(drwWindow**)lua_touserdata(L, 1);
	if(args == 1) {
		lua_pushstring(L, wnd->title().c_str());
		ret = 1;
	} else {
		if(!lua_isstring(L, 2)){
			luaL_error(L, "The argument to the title is not a string");
			return 1;
		}
		wnd->title(lua_tostring(L, 2));
		ret = 0;
	}
	return ret;
}

static const luaL_Reg winlib[] = {
	{"title", lua_window_title},
	{"show", lua_widget_show},
	{"hide", lua_widget_hide},
	{"__gc", lua_widget_gc},
	{NULL, NULL}
};

void lua_window_init(lua_State* L){
	luaL_newmetatable(L, DRW_LUA_WINDOW);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_register(L, NULL, winlib);
}
