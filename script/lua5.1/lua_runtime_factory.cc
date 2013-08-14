#include "../runtime.h"
#include "lua_runtime.h"

drwRuntime* drwRuntimeFactory::create(void){
	return new drwLuaRuntime;
};
