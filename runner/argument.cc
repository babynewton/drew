/*
The MIT License (MIT)

Copyright (c) 2013 drew

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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
