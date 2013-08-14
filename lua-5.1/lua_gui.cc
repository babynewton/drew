#include "lua_gui.h"
#include "log.h"
#include "lua_runtime.h"

#define DRW_LUA_WINDOW "drwLuaWindow"

static int lua_quit(lua_State* L){
	drwEngine* engine = drwLuaRuntime::engine();
	engine->quit();
	return 0;
}

static int lua_window(lua_State* L){
	drwEngine* engine = drwLuaRuntime::engine();
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

