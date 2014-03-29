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

#include <sstream>
#include <stdexcept>
#include "token.h"

drwTokenValue::drwTokenValue():
		m_token(DRW_TOKEN_NONE),
		m_log(drwLog::instance()),
		m_float(0.),
		m_int(0),
		m_bool(false)
{}

drwTokenValue::drwTokenValue(drwTokenValue& v):
		m_token(v.m_token),
		m_log(drwLog::instance()),
		m_string(v.m_string),
		m_float(v.m_float),
		m_int(v.m_int),
		m_bool(v.m_bool)
{}

void drwTokenValue::operator = (drwTokenValue token){
	m_token = token.m_token;
	m_string = token.m_string;
	m_float = token.m_float;
	m_int = token.m_int;
	m_bool = token.m_bool;
	m_log << verbose << "current token is " << to_string() << eol;
}

drwTokenValue::operator drwToken (void){
	return m_token;
}

drwTokenValue::operator const char* (void){
	return to_string();
}

const char* drwTokenValue::to_string(void){
	const char* tok_str[] = {
		"DRW_TOKEN_NONE",
		"DRW_TOKEN_SYMBOL",
		"DRW_TOKEN_FLOAT",
		"DRW_TOKEN_INTEGER",
		"DRW_TOKEN_STRING",
		"DRW_TOKEN_CODE",
		"DRW_TOKEN_BOOL",
		"DRW_TOKEN_SEPARATOR",
		"DRW_TOKEN_BEGINNING_OF_DICTIONARY",
		"DRW_TOKEN_END_OF_DICTIONARY",
		"DRW_TOKEN_BEGINNING_OF_LIST",
		"DRW_TOKEN_END_OF_LIST",
		"DRW_TOKEN_END_OF_FILE"
	};

	if(m_token >= DRW_TOKEN_MAX || m_token < 0) return "invalid";
	return tok_str[m_token];
}

bool drwTokenValue::boolean(void){
	return m_bool;
}

int drwTokenValue::integer_number(void){
	if (m_token != DRW_TOKEN_INTEGER) {
		stringstream ss;
		ss << ", An integer is expected, but got " << (const char*)m_token;
		throw logic_error(ss.str());
	}
	return m_int;
}

double drwTokenValue::floating_number(void){
	if (m_token != DRW_TOKEN_FLOAT) {
		stringstream ss;
		ss << ", A float is expected, but got " << (const char*)m_token;
		throw logic_error(ss.str());
	}
	return m_float;
}

string& drwTokenValue::text(void){
	if (m_token != DRW_TOKEN_STRING) {
		stringstream ss;
		ss << ", A string is expected, but got " << (const char*)m_token;
		throw logic_error(ss.str());
	}
	return m_string;
}

string& drwTokenValue::code(void){
	if (m_token != DRW_TOKEN_CODE) {
		stringstream ss;
		ss << ", A code is expeced, but got " << (const char*)m_token;
		throw logic_error(ss.str());
	}
	return m_string;
}

string& drwTokenValue::symbol(void){
	if (m_token != DRW_TOKEN_SYMBOL) {
		stringstream ss;
		ss << ", A symbol is expected, but got " << (const char*)m_token;
		throw logic_error(ss.str());
	}
	return m_string;
}

