#ifndef __DRW_RUNTIME_H__
#define __DRW_RUNTIME_H__

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "log.h"

class drwRuntime{
	private:
		drwLog& m_log;
		lua_State* m_runner;
		void failed(void);
	public:
		drwRuntime();
		~drwRuntime();
		void run(const char* code);
};

#endif //__DRW_RUNTIME_H__
