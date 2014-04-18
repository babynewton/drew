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

#include <vector>
#include <stdexcept>
#include <sstream>
#include <string.h>
#include "dml_parser.h"
#include "../config.h"

drwDmlParser::drwDmlParser():m_log(drwLog::instance()){}

void drwDmlParser::parse(const string path, drwDmlCallback* callback){
	drwScanner scanner(path);
	parse_a_header(scanner, callback);
	parse_a_dictionary(scanner, callback, true);
	m_log << debug << "drwDmlParser::parse is over" << eol;
	callback->onEnd();
}

void drwDmlParser::parse_a_header(drwScanner& scanner, drwDmlCallback* callback){
	drwTokenValue& token = scanner.scan();
	string symbol = token.symbol();
	{
		if(symbol != "version") throw logic_error("version is supposed to come");
		token = scanner.scan();
		if(token != DRW_TOKEN_SEPARATOR) throw logic_error(": is supposed");
		token = scanner.scan();
		if(DRW_DML_VERSION < token.floating_number()){
			stringstream ss;
			ss << "This DML(" << token.floating_number() << ") is later than the runner(" << DRW_DML_VERSION << ")";
			throw logic_error(ss.str());
		}
		m_log << verbose << "Version match : " << token.floating_number() << " vs " << DRW_DML_VERSION << eol;
	}
	{
		token = scanner.scan();
		symbol = token.symbol();
		if(symbol != "profile") throw logic_error("profile is supposed to come");
		token = scanner.scan();
		if(token != DRW_TOKEN_SEPARATOR) throw logic_error(": is supposed");
		token = scanner.scan();
		if(token.text() != callback->profile()) {
			stringstream ss;
			ss << "drw file has " << token.text() << " but the parser has " << callback->profile();
			throw logic_error(ss.str());
		}
	}
}

void drwDmlParser::parse_a_list(drwScanner& scanner, drwDmlCallback* callback){
	for(drwTokenValue& token = scanner.scan(); (drwToken)token != DRW_TOKEN_END_OF_FILE; token = scanner.scan()){
		if(token == DRW_TOKEN_END_OF_LIST){
			callback->onListClose();
			return;
		}
		string symbol;
		token = scanner.scan();
		switch(token){
			case DRW_TOKEN_INTEGER:
				callback->onValue(symbol, token.integer_number());
				break;
			case DRW_TOKEN_FLOAT:
				callback->onValue(symbol, token.floating_number());
				break;
			case DRW_TOKEN_STRING:
				callback->onValue(symbol, token.text());
				break;
			case DRW_TOKEN_BOOL:
				callback->onValue(symbol, token.boolean());
				break;
			case DRW_TOKEN_BEGINNING_OF_LIST:
				callback->onListOpen(symbol);
				parse_a_list(scanner, callback);
				break;
			case DRW_TOKEN_BEGINNING_OF_DICTIONARY:
				callback->onDictionaryOpen(symbol);
				parse_a_dictionary(scanner, callback);
				break;
			default:
				{
					stringstream ss;
					ss << "invalid token ";
					throw logic_error(ss.str());
				}
				break;
		}
	}
}

void drwDmlParser::parse_arguments(drwScanner& scanner, vector<string>& args){
	for(drwTokenValue& token = scanner.scan(); (drwToken)token != DRW_TOKEN_END_OF_FILE; token = scanner.scan()){
		switch(token){
			case DRW_TOKEN_END_OF_ARGUMENTS:
				return;
				break;
			case DRW_TOKEN_SYMBOL:
				args.push_back(token.symbol());
				break;
			default:
				{
					stringstream ss;
					ss << "invalid token ";
					throw logic_error(ss.str());
				}
				break;
		}
	}
}

void drwDmlParser::parse_code(string symbol, drwScanner& scanner, drwDmlCallback* callback){
	vector<string>args;
	parse_arguments(scanner, args);
	drwTokenValue& token = scanner.scan();
	if(token != DRW_TOKEN_CODE) throw logic_error("code is expected.");
	callback->onScript(symbol, token.code(), args);
}

void drwDmlParser::parse_a_dictionary(drwScanner& scanner, drwDmlCallback* callback, bool is_root){
	for(drwTokenValue& token = scanner.scan(); (drwToken)token != DRW_TOKEN_END_OF_FILE; token = scanner.scan()){
		if(token == DRW_TOKEN_END_OF_DICTIONARY){
			if(is_root) throw logic_error("invalid type token }");
			callback->onDictionaryClose();
			return;
		}
		string symbol = token.symbol();
		token = scanner.scan();
		switch(token){
			case DRW_TOKEN_SEPARATOR:
				token = scanner.scan();
				if(token == DRW_TOKEN_INTEGER) callback->onValue(symbol, token.integer_number());
				else if(token == DRW_TOKEN_FLOAT) callback->onValue(symbol, token.floating_number());
				else if(token == DRW_TOKEN_STRING) callback->onValue(symbol, token.text());
				else if(token == DRW_TOKEN_BOOL) callback->onValue(symbol, token.boolean());
				else throw logic_error("invalid type token");
				break;
			case DRW_TOKEN_BEGINNING_OF_LIST:
				callback->onListOpen(symbol);
				parse_a_list(scanner, callback);
				break;
			case DRW_TOKEN_BEGINNING_OF_DICTIONARY:
				callback->onDictionaryOpen(symbol);
				parse_a_dictionary(scanner, callback);
				break;
			case DRW_TOKEN_BEGINNING_OF_ARGUMENTS:
				parse_code(symbol, scanner, callback);
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
	if(!is_root){ //TODO:why?
		throw logic_error("} is missing");
	}
}

