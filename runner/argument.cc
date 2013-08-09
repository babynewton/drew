#include "argument.h"

drwArgument::drwArgument(int argc, char* argv[]){
	for(int i = 1 ; i < argc ; i++)
		m_path = argv[i];
}

string& drwArgument::path(void){
	return m_path;
}
