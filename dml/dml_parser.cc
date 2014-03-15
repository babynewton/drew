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

#include <stdexcept>
#include <sstream>
#include <string.h>
#include "dml_parser.h"
#include "scanner.h"
#include "../config.h"

drwDmlParser::drwDmlParser():m_log(drwLog::instance()){}

void drwDmlParser::parse(const string path, drwDmlCallback* callback){
	int structure_depth = 0;
	drwScanner scanner(path);
	drwToken token = DRW_TOKEN_NONE;
	while(token = scanner.scan(), token != DRW_TOKEN_END_OF_FILE){
		if(token == DRW_TOKEN_END_OF_DICTIONARY){
			if(structure_depth == 0) throw logic_error("Redundant {");
			callback->onStructureClose();
			structure_depth--;
			continue;
		}
		string symbol = scanner.symbol();
		DRW_SCAN_POLICY policy = DRW_SCAN_POLICY_NORMAL;
		if(m_script_symbols.find(symbol) != m_script_symbols.end()){
			policy = DRW_SCAN_POLICY_DICTIONARY_AS_CODE;
		}
		token = scanner.scan(policy);
		switch(token){
			case DRW_TOKEN_SEPARATOR:
				token = scanner.scan();
				if(token == DRW_TOKEN_INTEGER) callback->onValue(symbol, scanner.integer_number());
				else if(token == DRW_TOKEN_FLOAT) callback->onValue(symbol, scanner.floating_number());
				else if(token == DRW_TOKEN_STRING) callback->onValue(symbol, scanner.text());
				else if(token == DRW_TOKEN_BOOL) callback->onValue(symbol, scanner.boolean());
				else {
					stringstream ss;
					ss << "invalid type token";
					throw logic_error(ss.str());
				}
				break;
			case DRW_TOKEN_BEGINNING_OF_DICTIONARY:
				structure_depth++;
				callback->onStructureOpen(symbol);
				break;
			case DRW_TOKEN_CODE:
				callback->onScript(symbol, scanner.code());
				break;
			default:
				{
					stringstream ss;
					ss << "invalid token after symbol " << symbol;
					throw logic_error(ss.str());
				}
				break;
		}
	}
	callback->onEnd();
	m_log << debug << "drwDmlParser::parse is over" << eol;
}

void drwDmlParser::set_script_symbols(const char* script_symbols[]){
	for(int i = 0 ; script_symbols[i] ; i++)
		m_script_symbols[script_symbols[i]] = DRW_SCAN_POLICY_DICTIONARY_AS_CODE;
}
