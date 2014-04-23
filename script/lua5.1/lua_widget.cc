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

#include "lua_widget.h"
#include "log.h"

int lua_widget_show(lua_State* L){
	int args = lua_gettop(L);
	if(args < 1) { //ERROR
		luaL_error(L, "No widget object in the stack");
		return 1;
	}
	if(!lua_isuserdata(L, 1)){
		luaL_error(L, "The widget object is not an user data");
		return 1;
	}
	drwWidget* widget = *(drwWidget**)lua_touserdata(L, 1);
	bool all = false;
	if(args > 1) {
		if(!lua_isboolean(L, 2)){
			luaL_error(L, "The argument to show is not a boolean");
			return 1;
		}
		all = lua_toboolean(L, 2);
	}
	widget->show(all);
	return 0;
}

int lua_widget_hide(lua_State* L){
	int args = lua_gettop(L);
	if(args < 1) { //ERROR
		luaL_error(L, "No widget object in the stack");
		return 1;
	}
	if(!lua_isuserdata(L, 1)){
		luaL_error(L, "The widget object is not an user data");
		return 1;
	}
	drwWidget* widget = *(drwWidget**)lua_touserdata(L, 1);
	bool all = false;
	if(args > 1) {
		if(!lua_isboolean(L, 2)){
			luaL_error(L, "The argument to hide is not a boolean");
			return 1;
		}
		all = lua_toboolean(L, 2);
	}
	widget->hide(all);
	return 0;
}

