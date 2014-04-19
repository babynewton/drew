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
#include "log.h"

#define DRW_LUA_BOX "drwLuaBox"

int lua_hbox_new(lua_State* L, drwHBox* hbox){
	drwLog& log = drwLog::instance();
	log << verbose << "lua_hbox_as_this" << eol;
	drwHBox** box = (drwHBox**)lua_newuserdata(L, sizeof(drwBox*));
	*box = hbox;
	luaL_getmetatable(L, DRW_LUA_BOX);
	lua_setmetatable(L, -2);
	return 1;
}

int lua_hbox_as_this(lua_State* L, drwHBox* hbox){
	drwLog& log = drwLog::instance();
	log << verbose << "lua_hbox_as_this" << eol;
	drwHBox** box = (drwHBox**)lua_newuserdata(L, sizeof(drwBox*));
	luaL_getmetatable(L, DRW_LUA_BOX);
	lua_setmetatable(L, -2);
	*box = hbox;
	lua_setglobal(L, "this");
	return 0;
}

int lua_vbox_new(lua_State* L, drwVBox* vbox){
	drwLog& log = drwLog::instance();
	log << verbose << "lua_hbox_as_this" << eol;
	drwVBox** box = (drwVBox**)lua_newuserdata(L, sizeof(drwBox*));
	*box = vbox;
	luaL_getmetatable(L, DRW_LUA_BOX);
	lua_setmetatable(L, -2);
	return 1;
}

int lua_vbox_as_this(lua_State* L, drwVBox* vbox){
	drwLog& log = drwLog::instance();
	log << verbose << "lua_hbox_as_this" << eol;
	drwVBox** box = (drwVBox**)lua_newuserdata(L, sizeof(drwBox*));
	luaL_getmetatable(L, DRW_LUA_BOX);
	lua_setmetatable(L, -2);
	*box = vbox;
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
	drwHBox* box = *(drwHBox**)lua_touserdata(L, 1);
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
	drwHBox* box = *(drwHBox**)lua_touserdata(L, 1);
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

static int lua_box_homogenous(lua_State* L){
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
	drwHBox* box = *(drwHBox**)lua_touserdata(L, 1);
	if(args == 1) {
		lua_pushboolean(L, box->homogenous());
		ret = 1;
	} else {
		if(!lua_isboolean(L, 2)){
			luaL_error(L, "The argument to the homogenous is not a number");
			return 1;
		}
		box->homogenous(lua_toboolean(L, 2));
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
	drwHBox* box = *(drwHBox**)lua_touserdata(L, 1);
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

static int lua_box_gc(lua_State* L){
	int args = lua_gettop(L);
	if(args < 1) { //ERROR
		luaL_error(L, "No hbox object in the stack");
		return 1;
	}
	if(!lua_isuserdata(L, 1)){
		luaL_error(L, "The hbox object is not an user data");
		return 1;
	}
	drwHBox* box = *(drwHBox**)lua_touserdata(L, 1);
	delete box;
	return 0;
}

static const luaL_Reg boxlib[] = {
	{"spacing", lua_box_spacing},
	{"padding", lua_box_padding},
	{"homogenous", lua_box_homogenous},
	{"expand", lua_box_expand},
	{"__gc", lua_box_gc},
	{NULL, NULL}
};

void lua_box_init(lua_State* L){
	luaL_newmetatable(L, DRW_LUA_BOX);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_register(L, NULL, boxlib);
}
