#include "string.h"
#include "argument.h"

drwArgument::drwArgument(int argc, char* argv[]):m_verbose(false) {
	for(int i = 1 ; i < argc ; i++){
		if(!strcmp(argv[i], "-v") || !strcmp(argv[i], "--verbose")){
			m_verbose = true;
		}
		m_path = argv[i];
	}
}

string& drwArgument::path(void){
	return m_path;
}

bool drwArgument::verbose(void){
	return m_verbose;
}
