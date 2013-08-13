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
	m_line(1),
	m_path(path){
	m_string[0] = 0;
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
	m_end = m_begin + size;
	m_pointer = m_begin;
	if(size != fread(m_begin, 1, size, fd))
		throw runtime_error("fread failed");
	m_log << verbose << m_begin << eol;
	fclose(fd);
}

drwScanner::~drwScanner(){
	if(m_begin) delete m_begin;
}

string& drwScanner::symbol(void){
	if (m_token != DRW_TOKEN_SYMBOL) {
		stringstream ss;
		ss << m_path << ":" << m_line << ", A symbol is expected, but got " << (const char*)m_token;
		throw logic_error(ss.str());
	}
	return m_string;
}

string& drwScanner::text(void){
	if (m_token != DRW_TOKEN_STRING) {
		stringstream ss;
		ss << m_path << ":" << m_line << ", A string is expected, but got " << (const char*)m_token;
		throw logic_error(ss.str());
	}
	return m_string;
}

string& drwScanner::code(void){
	if (m_token != DRW_TOKEN_CODE) {
		stringstream ss;
		ss << m_path << ":" << m_line << ", A code is expeced, but got " << (const char*)m_token;
		throw logic_error(ss.str());
	}
	return m_string;
}

drwToken drwScanner::scan_a_string(char endc){
	char buffer[DRW_SCAN_BUFFER_SIZE];
	char* pt = buffer;
	char* endp = pt + DRW_SCAN_BUFFER_SIZE - 1;
	*endp = 0;
	m_string.clear();
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
			m_string += buffer;
			pt = buffer;
		}
	}
	if(pt != buffer) {
		*pt = 0;
		m_string += buffer;
	}
	m_pointer++;
	m_log << verbose << "drwScanner:;scan_a_string(" << endc << ") scanned " << m_string << eol;
	return (endc == '}') ? DRW_TOKEN_CODE : DRW_TOKEN_STRING;
}

drwToken drwScanner::scan_a_symbol(void){
	char buffer[DRW_SCAN_BUFFER_SIZE];
	char* pt = buffer;
	char* endp = pt + DRW_SCAN_BUFFER_SIZE - 1;
	*endp = 0;
	m_string.clear();
	while(isalnum(*m_pointer) || *m_pointer == '_'){
		*pt++ = *m_pointer++;
		if(pt == endp) {
			m_string += buffer;
			pt = buffer;
		}
	}
	if(pt != buffer) {
		*pt = 0;
		m_string += buffer;
	}
	return DRW_TOKEN_SYMBOL;
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

drwToken drwScanner::scan_a_number(void){
	char buffer[DRW_SCAN_BUFFER_SIZE];
	char* pt = buffer;
	char* endp = pt + DRW_SCAN_BUFFER_SIZE - 1;
	*endp = 0;
	if(*m_pointer == '+') m_pointer++;
	else if(*m_pointer == '-') *pt++ = *m_pointer++;
	while(isdigit(*m_pointer)) *pt++ = *m_pointer++;
	if(*m_pointer != '.') {
		*pt = 0;
		m_int = atoi(buffer);
		return DRW_TOKEN_INTEGER;
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
			m_float = atof(buffer);
			return DRW_TOKEN_FLOAT;
			break;
	}
	if(*m_pointer == '+') m_pointer++;
	else if(*m_pointer == '-') *pt++ = *m_pointer++;
	while(isdigit(*m_pointer)) *pt++ = *m_pointer++;
	*pt = 0;
	m_float = atof(buffer);
	return DRW_TOKEN_FLOAT;
}

void drwScanner::skip_a_line(void){
	while(*m_pointer != '\r' && *m_pointer != '\n') m_pointer++;
}

drwToken drwScanner::scan(unsigned int policy){
	do{
		switch(*m_pointer){
			case '#':
				skip_a_line();
				break;
			case '\"':
				m_pointer++;
				m_token = scan_a_string('\"');
				return m_token;
				break;
			case '{':
				m_pointer++;
				m_token = (policy & DRW_SCAN_POLICY_DICTIONARY_AS_CODE) ? scan_a_string('}') : DRW_TOKEN_BEGINNING_OF_DICTIONARY;
				return m_token;
				break;
			case '}':
				m_pointer++;
				m_token = DRW_TOKEN_END_OF_DICTIONARY;
				return m_token;
				break;
			case '[':
				m_pointer++;
				m_token = DRW_TOKEN_BEGINNING_OF_LIST;
				return m_token;
				break;
			case ']':
				m_pointer++;
				m_token = DRW_TOKEN_END_OF_LIST;
				return m_token;
				break;
			case ':':
				m_pointer++;
				m_token = DRW_TOKEN_SEPARATOR;
				return m_token;
				break;
			case '+':
			case '-':
				m_token = scan_a_number();
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
		if(isalpha(*m_pointer)) {
			m_token = scan_a_symbol();
			return m_token;
		} else if(isdigit(*m_pointer)) {
			m_token = scan_a_number();
			return m_token;
		}
	}while(m_pointer < m_end);
	m_token = DRW_TOKEN_END_OF_FILE;
	return m_token;
}

int drwScanner::integer_number(void){
	if (m_token != DRW_TOKEN_INTEGER) {
		stringstream ss;
		ss << m_path << ":" << m_line << ", An integer is expected, but got " << (const char*)m_token;
		throw logic_error(ss.str());
	}
	return m_int;
}
double drwScanner::floating_number(void){
	if (m_token != DRW_TOKEN_FLOAT) {
		stringstream ss;
		ss << m_path << ":" << m_line << ", A float is expected, but got " << (const char*)m_token;
		throw logic_error(ss.str());
	}
	return m_float;
}

