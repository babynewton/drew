#ifndef __DRW_LUA_RUNTIME_H__
#define __DRW_LUA_RUNTIME_H__

#include "engine.h"

class drwLuaRuntime{
	public:
		static void engine(drwEngine* engine);
		static drwEngine* engine(void);
};

#endif //__DRW_LUA_RUNTIME_H__
