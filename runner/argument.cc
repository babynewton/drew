/*
The MIT License (MIT)

Copyright (c) 2013 Newton Kim

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

drwArgument::drwArgument(int argc, char* argv[]):
	m_log_level(DRW_LOG_LEVEL_NONE),
	m_help(false),
	m_version(false),
	m_banner(false)
{
	for(int i = 1 ; i < argc ; i++){
		if(!strcmp(argv[i], "-d") || !strcmp(argv[i], "--debug")){
			m_log_level = DRW_LOG_LEVEL_DEBUG;
		} else if(!strcmp(argv[i], "-v") || !strcmp(argv[i], "--verbose")){
		} else if(!strcmp(argv[i], "--version")){
			m_version = true;
		} else if(!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")){
			m_help = true;
		} else if(!strcmp(argv[i], "-b") || !strcmp(argv[i], "--banner")){
			m_banner = true;
		} else if(argv[i][0] != '-'){
			if(m_path.empty()) m_path = argv[i];
			else m_args.push_back(argv[i]);
		}
	}
}

string& drwArgument::path(void){
	return m_path;
}

drwLogLevel drwArgument::log_level(void){
	return m_log_level;
}

bool drwArgument::help(void){
	return m_help;
}

bool drwArgument::version(void){
	return m_version;
}

bool drwArgument::banner(void){
	return m_banner;
}

vector<string>& drwArgument::arguments(void){
	return m_args;
}

