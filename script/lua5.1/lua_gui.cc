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

#include "lua_gui.h"
#include "log.h"
#include "engine.h"
#include "lua_window.h"
#include "lua_button.h"


static int lua_quit(lua_State* L){
	drwEngine* engine = drwEngine::current();
	engine->quit();
	return 0;
}

int lua_widget_new(lua_State* L, drwWidget* widget){
	int ret = 0;
	switch(widget->type){
		case DRW_WIDGET_TYPE_WINDOW:
			ret = lua_window_new(L, (drwWindow*) widget);
			break;
		case DRW_WIDGET_TYPE_BUTTON:
			ret = lua_button_new(L, (drwButton*) widget);
			break;
	}
	return ret;
}

int lua_widget_as_this(lua_State* L, drwWidget* widget){
	int ret = 0;
	if(!widget) return ret;
	switch(widget->type){
		case DRW_WIDGET_TYPE_WINDOW:
			ret = lua_window_as_this(L, (drwWindow*) widget);
			break;
		case DRW_WIDGET_TYPE_BUTTON:
			ret = lua_button_as_this(L, (drwButton*) widget);
			break;
	}
	return ret;
}

static int lua_gui_find(lua_State* L){
	drwEngine* engine = drwEngine::current();
	string wid;
	if(!lua_gettop(L)){
		lua_pushnil(L);
		lua_pushstring(L, "No argument has been passed.");
		return 2;
	}
	if(!lua_isstring(L, 1)) {
		lua_pushnil(L);
		lua_pushstring(L, "The 1st argument is not a string.");
		return 2;
	}
	wid = lua_tostring(L, 1);
	drwWidget* widget = NULL;
	try{
		widget = engine->cache(wid);
	} catch(exception& e){
		lua_pushnil(L);
		lua_pushstring(L, e.what());
		return 2;
	}
	return lua_widget_new(L, widget);
}

static const luaL_Reg guilib[] = {
	{"quit", lua_quit},
	{"find", lua_gui_find},
	{NULL, NULL}
};

LUALIB_API int luaopen_gui(lua_State* L){
	lua_window_init(L);
	lua_button_init(L);
	luaL_register(L, "gui", guilib);
	return 1;
}

