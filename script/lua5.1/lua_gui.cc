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
#include "window.h"
#include "button.h"

#define DRW_LUA_WINDOW "drwLuaWindow"
#define DRW_LUA_BUTTON "drwLuaButton"

static int lua_quit(lua_State* L){
	drwEngine* engine = drwEngine::current();
	engine->quit();
	return 0;
}

static int lua_window(lua_State* L){
	drwEngine* engine = drwEngine::current();
	if(!engine->top()){
		lua_pushnil(L);
		lua_pushstring(L, "Window is not allocated yet");
		return 2;
	}
	drwWidget** widget = (drwWidget**)lua_newuserdata(L, sizeof(drwWidget*));
	luaL_getmetatable(L, DRW_LUA_WINDOW);
	lua_setmetatable(L, -2);
	*widget = engine->top();
	return 1;
}

static int lua_window_new(lua_State* L, drwWindow* window){
	drwWindow** wnd = (drwWindow**)lua_newuserdata(L, sizeof(drwWindow*));
	*wnd = window;
	luaL_getmetatable(L, DRW_LUA_WINDOW);
	lua_setmetatable(L, -2);
	return 1;
}

static int lua_button_new(lua_State* L, drwButton* button){
	drwLog& log = drwLog::instance();
	log << verbose << "lua_button_as_this" << eol;
	drwButton** btn = (drwButton**)lua_newuserdata(L, sizeof(drwButton*));
	*btn = button;
	luaL_getmetatable(L, DRW_LUA_BUTTON);
	lua_setmetatable(L, -2);
	return 1;
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

static int lua_window_as_this(lua_State* L, drwWindow* window){
	drwWindow** wnd = (drwWindow**)lua_newuserdata(L, sizeof(drwWindow*));
	luaL_getmetatable(L, DRW_LUA_WINDOW);
	lua_setmetatable(L, -2);
	*wnd = window;
	lua_setglobal(L, "this");
	return 0;
}

static int lua_button_as_this(lua_State* L, drwButton* button){
	drwLog& log = drwLog::instance();
	log << verbose << "lua_button_as_this" << eol;
	drwButton** btn = (drwButton**)lua_newuserdata(L, sizeof(drwButton*));
	luaL_getmetatable(L, DRW_LUA_BUTTON);
	lua_setmetatable(L, -2);
	*btn = button;
	lua_setglobal(L, "this");
	return 0;
}

int lua_widget_as_this(lua_State* L, drwWidget* widget){
	int ret = 0;
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

static int lua_button_label(lua_State* L){
	int args = lua_gettop(L);
	int ret = 0;
	if(args < 1) { //ERROR
		luaL_error(L, "No button object in the stack");
		return 1;
	}
	if(!lua_isuserdata(L, 1)){
		luaL_error(L, "The button object is not an user data");
		return 1;
	}
	drwButton* btn = *(drwButton**)lua_touserdata(L, 1);
	if(args == 1) {
		lua_pushstring(L, btn->label().c_str());
		ret = 1;
	} else {
		if(!lua_isstring(L, 2)){
			luaL_error(L, "The argument to the label is not a string");
			return 1;
		}
		btn->label(lua_tostring(L, 2));
		ret = 0;
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
	{"window", lua_window},
	{"find", lua_gui_find},
	{NULL, NULL}
};

static const luaL_Reg winlib[] = {
	{NULL, NULL}
};

static const luaL_Reg btnlib[] = {
	{"label", lua_button_label},
	{NULL, NULL}
};

LUALIB_API int luaopen_gui(lua_State* L){
	luaL_newmetatable(L, DRW_LUA_WINDOW);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_register(L, NULL, winlib);
	luaL_newmetatable(L, DRW_LUA_BUTTON);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_register(L, NULL, btnlib);
	luaL_register(L, "gui", guilib);
	return 1;
}

