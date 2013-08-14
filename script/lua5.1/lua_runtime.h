#ifndef __DRW_LUA_RUNTIME_H__
#define __DRW_LUA_RUNTIME_H__

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "log.h"
#include "../runtime.h"

class drwLuaRuntime: public drwRuntime{
	private:
		drwLog& m_log;
		lua_State* m_runner;
		void failed(void);
	public:
		drwLuaRuntime();
		~drwLuaRuntime();
		void run(const char* code, int nresults = 0);
		bool result(void);
};

#endif //__DRW_LUA_RUNTIME_H__
