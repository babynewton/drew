#include <iostream>
#include "lua_log.h"
#include "log.h"

static int cout_print(lua_State* L){
	while(lua_gettop(L)) {
		cout << lua_tostring(L, -1);
		lua_pop(L, 1);
	}
	cout << endl;
	return 0;
}

static const luaL_Reg coutlib[] = {
	{"print", cout_print},
	{NULL, NULL}
};

LUALIB_API int luaopen_cout(lua_State* L){
	luaL_register(L, "cout", coutlib);
	 return 1;
}
