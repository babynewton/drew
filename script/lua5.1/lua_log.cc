#include "lua_log.h"
#include "log.h"

static int log_verbose(lua_State* L){
	drwLog& log = drwLog::instance();
	log << verbose;
	while(lua_gettop(L)) {
		log << lua_tostring(L, -1);
		lua_pop(L, 1);
	}
	log << eol;
	return 0;
}

static int log_debug(lua_State* L){
	drwLog& log = drwLog::instance();
	log << debug;
	while(lua_gettop(L)) {
		log << lua_tostring(L, -1);
		lua_pop(L, 1);
	}
	log << eol;
	return 0;
}

static const luaL_Reg loglib[] = {
	{"verbose", log_verbose},
	{"debug", log_debug},
	{NULL, NULL}
};

LUALIB_API int luaopen_log(lua_State* L){
	luaL_register(L, "log", loglib);
	 return 1;
}
