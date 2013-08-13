#include "lua_gui.h"
#include "log.h"

static int log_verbose(lua_State* L){
	drwLog& log = drwLog::instance();
	log << verbose << "log_verbose" << eol;
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
	return 1;
}

LUALIB_API int luaopen_log(lua_State* L){
	luaL_register(L, "log", loglib);
	 return 1;
}
