#include "lua_gui.h"

static int log_verbose(lua_State* L){
	return 0;
}

static const luaL_Reg guilib[] = {
	{NULL, NULL}
};

static const luaL_Reg loglib[] = {
	{"verbose", log_verbose},
	{NULL, NULL}
};

LUALIB_API int luaopen_gui(lua_State* L){
	luaL_register(L, "gui", guilib);
	luaL_register(L, "log", loglib);
	 return 1;
}
