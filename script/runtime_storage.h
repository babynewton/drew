#ifndef __DRW_RUNTIME_STORAGE_H__
#define __DRW_RUNTIME_STORAGE_H__

#include "engine.h"

class drwRuntimeStorage{
	public:
		static void engine(drwEngine* engine);
		static drwEngine* engine(void);
};

#endif //__DRW_RUNTIME_STORAGE_H__
