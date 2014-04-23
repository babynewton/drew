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

#include "lua_box.h"
#include "lua_widget.h"
#include "log.h"

#define DRW_LUA_BOX "drwLuaBox"

int lua_box_new(lua_State* L, drwBox* hbox){
	drwLog& log = drwLog::instance();
	log << verbose << "lua_box_new" << eol;
	drwBox** box = (drwBox**)lua_newuserdata(L, sizeof(drwBox*));
	*box = hbox;
	luaL_getmetatable(L, DRW_LUA_BOX);
	lua_setmetatable(L, -2);
	return 1;
}

int lua_box_as_this(lua_State* L, drwBox* hbox){
	drwLog& log = drwLog::instance();
	log << verbose << "lua_box_as_this" << eol;
	drwBox** box = (drwBox**)lua_newuserdata(L, sizeof(drwBox*));
	luaL_getmetatable(L, DRW_LUA_BOX);
	lua_setmetatable(L, -2);
	*box = hbox;
	lua_setglobal(L, "this");
	return 0;
}

static int lua_box_spacing(lua_State* L){
	int args = lua_gettop(L);
	int ret = 0;
	if(args < 1) { //ERROR
		luaL_error(L, "No hbox object in the stack");
		return 1;
	}
	if(!lua_isuserdata(L, 1)){
		luaL_error(L, "The hbox object is not an user data");
		return 1;
	}
	drwBox* box = *(drwBox**)lua_touserdata(L, 1);
	if(args == 1) {
		lua_pushinteger(L, box->spacing());
		ret = 1;
	} else {
		if(!lua_isnumber(L, 2)){
			luaL_error(L, "The argument to the spacing is not a number");
			return 1;
		}
		box->spacing(lua_tonumber(L, 2));
		ret = 0;
	}
	return ret;
}

static int lua_box_padding(lua_State* L){
	int args = lua_gettop(L);
	int ret = 0;
	if(args < 1) { //ERROR
		luaL_error(L, "No hbox object in the stack");
		return 1;
	}
	if(!lua_isuserdata(L, 1)){
		luaL_error(L, "The hbox object is not an user data");
		return 1;
	}
	drwBox* box = *(drwBox**)lua_touserdata(L, 1);
	if(args == 1) {
		lua_pushinteger(L, box->padding());
		ret = 1;
	} else {
		if(!lua_isnumber(L, 2)){
			luaL_error(L, "The argument to the padding is not a number");
			return 1;
		}
		box->padding(lua_tonumber(L, 2));
		ret = 0;
	}
	return ret;
}

static int lua_box_homogeneous(lua_State* L){
	int args = lua_gettop(L);
	int ret = 0;
	if(args < 1) { //ERROR
		luaL_error(L, "No hbox object in the stack");
		return 1;
	}
	if(!lua_isuserdata(L, 1)){
		luaL_error(L, "The hbox object is not an user data");
		return 1;
	}
	drwBox* box = *(drwBox**)lua_touserdata(L, 1);
	if(args == 1) {
		lua_pushboolean(L, box->homogeneous());
		ret = 1;
	} else {
		if(!lua_isboolean(L, 2)){
			luaL_error(L, "The argument to the homogeneous is not a number");
			return 1;
		}
		box->homogeneous(lua_toboolean(L, 2));
		ret = 0;
	}
	return ret;
}

static int lua_box_expand(lua_State* L){
	int args = lua_gettop(L);
	int ret = 0;
	if(args < 1) { //ERROR
		luaL_error(L, "No hbox object in the stack");
		return 1;
	}
	if(!lua_isuserdata(L, 1)){
		luaL_error(L, "The hbox object is not an user data");
		return 1;
	}
	drwBox* box = *(drwBox**)lua_touserdata(L, 1);
	if(args == 1) {
		lua_pushboolean(L, box->expand());
		ret = 1;
	} else {
		if(!lua_isboolean(L, 2)){
			luaL_error(L, "The argument to the expand is not a number");
			return 1;
		}
		box->expand(lua_toboolean(L, 2));
		ret = 0;
	}
	return ret;
}

static int lua_box_fill(lua_State* L){
	int args = lua_gettop(L);
	int ret = 0;
	if(args < 1) { //ERROR
		luaL_error(L, "No hbox object in the stack");
		return 1;
	}
	if(!lua_isuserdata(L, 1)){
		luaL_error(L, "The hbox object is not an user data");
		return 1;
	}
	drwBox* box = *(drwBox**)lua_touserdata(L, 1);
	if(args == 1) {
		lua_pushboolean(L, box->fill());
		ret = 1;
	} else {
		if(!lua_isboolean(L, 2)){
			luaL_error(L, "The argument to the fill is not a number");
			return 1;
		}
		box->fill(lua_toboolean(L, 2));
		ret = 0;
	}
	return ret;
}

static const luaL_Reg boxlib[] = {
	{"spacing", lua_box_spacing},
	{"padding", lua_box_padding},
	{"homogeneous", lua_box_homogeneous},
	{"expand", lua_box_expand},
	{"fill", lua_box_fill},
	{"show", lua_widget_show},
	{"hide", lua_widget_hide},
	{"__gc", lua_widget_gc},
	{NULL, NULL}
};

void lua_box_init(lua_State* L){
	luaL_newmetatable(L, DRW_LUA_BOX);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_register(L, NULL, boxlib);
}
