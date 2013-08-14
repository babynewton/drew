#include <stdexcept>
#include "lua_runtime.h"
#include "lua_gui.h"
#include "lua_log.h"
#include "lua_cout.h"

drwLuaRuntime::drwLuaRuntime():m_log(drwLog::instance()), m_runner(luaL_newstate()){
	luaL_openlibs(m_runner);
	lua_pushliteral(m_runner, "log");
	luaopen_log(m_runner);
	lua_pushliteral(m_runner, "gui");
	luaopen_gui(m_runner);
	lua_pushliteral(m_runner, "cout");
	luaopen_cout(m_runner);
}

drwLuaRuntime::~drwLuaRuntime(){
	lua_close(m_runner);
}

void drwLuaRuntime::failed(void){
	const char* err = lua_tostring(m_runner, -1);
	m_log << debug << err << eol;
	throw runtime_error(err);
}

void drwLuaRuntime::run(const char* code, int results){
	if (luaL_loadstring(m_runner, code)) failed();
	if(lua_pcall(m_runner, 0, results, 0)) failed();
}

bool drwLuaRuntime::result(void){
	if(!lua_gettop(m_runner)) throw runtime_error("Tried to get un-returned result");
	if(!lua_isboolean(m_runner, -1)) throw runtime_error("Returned result is not a boolean");
	return (lua_toboolean(m_runner, -1)) ? true : false;
}
