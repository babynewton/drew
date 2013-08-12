#include "string.h"
#include "argument.h"

drwArgument::drwArgument(int argc, char* argv[]):m_log_level(DRW_LOG_LEVEL_NONE) {
	for(int i = 1 ; i < argc ; i++){
		if(!strcmp(argv[i], "-d") || !strcmp(argv[i], "--debug")){
			m_log_level = DRW_LOG_LEVEL_DEBUG;
		} else if(!strcmp(argv[i], "-v") || !strcmp(argv[i], "--verbose")){
			m_log_level = DRW_LOG_LEVEL_VERBOSE;
		} else {
			m_path = argv[i];
		}
	}
}

string& drwArgument::path(void){
	return m_path;
}

drwLogLevel drwArgument::log_level(void){
	return m_log_level;
}
