#include <stdexcept>
#include "runtime_storage.h"

static drwEngine* s_engine;
void drwRuntimeStorage::engine(drwEngine* engine){
	if(s_engine) throw runtime_error("The engine has been already set");
	s_engine = engine;
}

drwEngine* drwRuntimeStorage::engine(void){
	if(!s_engine) throw runtime_error("The engine has not been set");
	return s_engine;
}
