#ifndef __DRW_RUNTIME_H__
#define __DRW_RUNTIME_H__

class drwRuntime{
	public:
		virtual void run(const char* code, int nresults = 0) = 0;
		virtual bool result(void) = 0;
};

class drwRuntimeFactory{
	public:
		static drwRuntime* create(void);
};
#endif //__DRW_RUNTIME_H__
