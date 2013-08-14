#include <stdexcept>
#include "lua_runtime.h"

static drwEngine* s_engine;
void drwLuaRuntime::engine(drwEngine* engine){
	if(s_engine) throw runtime_error("The engine has been already set");
	s_engine = engine;
}

drwEngine* drwLuaRuntime::engine(void){
	if(!s_engine) throw runtime_error("The engine has not been set");
	return s_engine;
}
