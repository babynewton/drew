#include <stdexcept>
#include "runtime.h"
#include "lua_gui.h"

drwRuntime::drwRuntime():m_log(drwLog::instance()), m_runner(luaL_newstate()){
	luaL_openlibs(m_runner);
	lua_pushliteral(m_runner, "log");
	luaopen_log(m_runner);
	lua_pushliteral(m_runner, "gui");
	luaopen_gui(m_runner);
}

drwRuntime::~drwRuntime(){
	lua_close(m_runner);
}

void drwRuntime::failed(void){
	const char* err = lua_tostring(m_runner, -1);
	m_log << debug << err << eol;
	throw runtime_error(err);
}

void drwRuntime::run(const char* code){
	if (luaL_loadstring(m_runner, code)) failed();
	if(lua_pcall(m_runner, 0, 0, 0)) failed();
}
