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

#include "application_parser.h"

drwApplicationParser(drwEngine* engine):m_log(drwLog::instance()), m_engine(engine){
}

void drwApplicationParser::onValue(const string name, const int value){
}

void drwApplicationParser::onValue(const string name, const double value){
	if(name == "version"){
		if(DRW_DML_VERSION < value){
			stringstream ss;
			ss << "This DML(" << value << ") is later than the runner(" << DRW_DML_VERSION << ")";
			throw logic_error(ss.str());
		}
		m_log << verbose << "Version match : " << scanner.floating_number() << " vs " << DRW_DML_VERSION << eol;
	}
}

void drwApplicationParser::onValue(const string name, const string value){
}

void drwApplicationParser::onScript(const string name, const string script){
}

void drwApplicationParser::onStructureOpen(const string name){
}

void drwApplicationParser::onStructureClose(void){
}


