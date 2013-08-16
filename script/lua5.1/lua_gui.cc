/*
The MIT License (MIT)

Copyright (c) 2013 drew

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

#include "lua_gui.h"
#include "log.h"
#include "../runtime_storage.h"

#define DRW_LUA_WINDOW "drwLuaWindow"

static int lua_quit(lua_State* L){
	drwEngine* engine = drwRuntimeStorage::engine();
	engine->quit();
	return 0;
}

static int lua_window(lua_State* L){
	drwEngine* engine = drwRuntimeStorage::engine();
	if(!engine->window()){
		lua_pushnil(L);
		lua_pushstring(L, "Window is not allocated yet");
		return 2;
	}
	drwWindow** window = (drwWindow**)lua_newuserdata(L, sizeof(drwWindow*));
	luaL_getmetatable(L, DRW_LUA_WINDOW);
	lua_setmetatable(L, -2);
	*window = engine->window();
	return 1;
}

static const luaL_Reg guilib[] = {
	{"quit", lua_quit},
	{"window", lua_window},
	{NULL, NULL}
};

static const luaL_Reg winlib[] = {
	{NULL, NULL}
};

LUALIB_API int luaopen_gui(lua_State* L){
	luaL_newmetatable(L, DRW_LUA_WINDOW);
	luaL_register(L, NULL, winlib);
	luaL_register(L, "gui", guilib);
	return 1;
}

