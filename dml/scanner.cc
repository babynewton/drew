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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdexcept>
#include <sstream>
#include "scanner.h"

using namespace std;

#define DRW_SCAN_BUFFER_SIZE 128

drwScanner::drwScanner(const string& path):
	m_log(drwLog::instance()),
	m_begin(NULL),
	m_path(path){
	m_token.m_string[0] = 0;
	FILE* fd = fopen(path.c_str(), "rb");
	if(!fd) throw runtime_error(strerror(errno));
	int end = fseek(fd, 0, SEEK_END);
	if(end == -1) throw runtime_error(strerror(errno));
	end = ftell(fd);
	int begin = fseek(fd, 0, SEEK_SET);
	if(begin == -1) throw runtime_error(strerror(errno));
	begin = ftell(fd);
	unsigned int size = end - begin;
	m_begin = new char [size];
	if(!m_begin) throw runtime_error("m_stream allocation failed");
	m_log << debug << size << " bytes has been allocated" << eol;
	m_end = m_begin + size - 1;
	m_pointer = m_begin;
	unsigned int asz = fread(m_begin, 1, size, fd);
	if(size != asz){
		m_log << debug << "tried to read " << size << "bytes, but actually read " << asz << eol;
		throw runtime_error("fread failed");
	}
	m_log << verbose << m_begin << eol;
	fclose(fd);
}

drwScanner::~drwScanner(){
	if(m_begin) delete m_begin;
}

void drwScanner::scan_a_string(char endc){
	char buffer[DRW_SCAN_BUFFER_SIZE];
	char* pt = buffer;
	char* endp = pt + DRW_SCAN_BUFFER_SIZE - 1;
	*endp = 0;
	m_token.m_string.clear();
	unsigned int depth = 0;
	while(*m_pointer != endc || depth){
		switch(*m_pointer){
			case '{':
				depth++;
				break;
			case '}':
				depth--;
				break;
			case '\r':
				if(*(m_pointer - 1) != '\n') m_line++;
				break;
			case '\n':
				if(*(m_pointer - 1) != '\r') m_line++;
				break;
		}
		*pt++ = *m_pointer++;
		if(pt == endp) {
			m_token.m_string += buffer;
			pt = buffer;
		}
	}
	if(pt != buffer) {
		*pt = 0;
		m_token.m_string += buffer;
	}
	m_pointer++;
	m_log << verbose << "drwScanner::scan_a_string(" << endc << ") scanned " << m_token.m_string << eol;
	m_token.m_token = (endc == '}') ? DRW_TOKEN_CODE : DRW_TOKEN_STRING;
}

void drwScanner::scan_a_symbol(void){
	char buffer[DRW_SCAN_BUFFER_SIZE];
	char* pt = buffer;
	char* endp = pt + DRW_SCAN_BUFFER_SIZE - 1;
	*endp = 0;
	m_token.m_string.clear();
	while(isalnum(*m_pointer) || *m_pointer == '_'){
		*pt++ = *m_pointer++;
		if(pt == endp) {
			m_token.m_string += buffer;
			pt = buffer;
		}
	}
	if(pt != buffer) {
		*pt = 0;
		m_token.m_string += buffer;
	}
	m_log << verbose << "drwScanner::scan_a_symbol() scanned " << m_token.m_string << eol;
	if(m_token.m_string == "true"){
		m_token.m_string.clear();
		m_token.m_token = DRW_TOKEN_BOOL;
		m_token.m_bool = true;
	} else if (m_token.m_string == "false"){
		m_token.m_string.clear();
		m_token.m_token = DRW_TOKEN_BOOL;
		m_token.m_bool = false;
	} else {
		m_token.m_token = DRW_TOKEN_SYMBOL;
	}
}

void drwScanner::scan_eol(void){
	switch(*m_pointer){
		case '\r':
			if(*(m_pointer + 1) == '\n') m_pointer++;
			m_line++;
			break;
		case '\n':
			if(*(m_pointer + 1) == '\r') m_pointer++;
			m_line++;
			break;
		case ';':
			break;
	}
	m_log << verbose << "eol to " << m_line << eol;
	m_pointer++;
}

void drwScanner::scan_a_number(void){
	char buffer[DRW_SCAN_BUFFER_SIZE];
	char* pt = buffer;
	char* endp = pt + DRW_SCAN_BUFFER_SIZE - 1;
	*endp = 0;
	if(*m_pointer == '+') m_pointer++;
	else if(*m_pointer == '-') *pt++ = *m_pointer++;
	while(isdigit(*m_pointer)) *pt++ = *m_pointer++;
	if(*m_pointer != '.') {
		*pt = 0;
		m_token.m_int = atoi(buffer);
		m_log << verbose << "drwScanner::scan_a_number() scanned " << m_token.m_int << eol;
		m_token.m_token = DRW_TOKEN_INTEGER;
		return;
	} else {
		*pt++ = *m_pointer++;
	}
	while(isdigit(*m_pointer)) *pt++ = *m_pointer++;
	switch(*m_pointer){
		case 'e':
		case 'E':
		case 'd':
		case 'D':
			*pt++ = *m_pointer++;
			break;
		default:
			*pt = 0;
			m_log << verbose << "m_float << " << buffer << eol;
			m_token.m_float = atof(buffer);
			m_log << verbose << "drwScanner::scan_a_number() scanned " << m_token.m_float << eol;
			m_token.m_token = DRW_TOKEN_FLOAT;
			return;
			break;
	}
	if(*m_pointer == '+') m_pointer++;
	else if(*m_pointer == '-') *pt++ = *m_pointer++;
	while(isdigit(*m_pointer)) *pt++ = *m_pointer++;
	*pt = 0;
	m_token.m_float = atof(buffer);
	m_log << verbose << "drwScanner::scan_a_number() scanned " << m_token.m_float << eol;
	m_token.m_token = DRW_TOKEN_FLOAT;
}

void drwScanner::skip_a_line(void){
	while(*m_pointer != '\r' && *m_pointer != '\n') m_pointer++;
}

drwTokenValue& drwScanner::scan(void){
	while(m_pointer < m_end){
//		m_log << verbose << (int)m_pointer << " : " << (int) m_end << eol;
		switch(*m_pointer){
			case '#':
				skip_a_line();
				break;
			case '\"':
				m_pointer++;
				scan_a_string('\"');
				return m_token;
				break;
			case '{':
				m_pointer++;
				if (m_token.m_token == DRW_TOKEN_END_OF_ARGUMENTS){
					scan_a_string('}');
				} else {
					m_token.m_token = DRW_TOKEN_BEGINNING_OF_DICTIONARY;
				}
				return m_token;
				break;
			case '}':
				m_pointer++;
				m_token.m_token = DRW_TOKEN_END_OF_DICTIONARY;
				return m_token;
				break;
			case '(':
				m_pointer++;
				m_token.m_token = DRW_TOKEN_BEGINNING_OF_ARGUMENTS;
				return m_token;
				break;
			case ')':
				m_pointer++;
				m_token.m_token = DRW_TOKEN_END_OF_ARGUMENTS;
				return m_token;
				break;
			case '[':
				m_pointer++;
				m_token.m_token = DRW_TOKEN_BEGINNING_OF_LIST;
				return m_token;
				break;
			case ']':
				m_pointer++;
				m_token.m_token = DRW_TOKEN_END_OF_LIST;
				return m_token;
				break;
			case ':':
				m_pointer++;
				m_token.m_token = DRW_TOKEN_SEPARATOR;
				return m_token;
				break;
			case '+':
			case '-':
				scan_a_number();
				return m_token;
				break;
			case '\r':
			case '\n':
			case ';':
				scan_eol();
				break;
			case ' ':
			case '\t':
				m_pointer++;
				break;
		}
		if(isalpha(*m_pointer) || *m_pointer == '_') {
			scan_a_symbol();
			return m_token;
		} else if(isdigit(*m_pointer)) {
			scan_a_number();
			return m_token;
		}
	};
	m_token.m_token = DRW_TOKEN_END_OF_FILE;
	return m_token;
}

