#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdexcept>
#include "scanner.h"

static const char* s_token_sting[] = {
	"DRW_TOKEN_NONE",
	"DRW_TOKEN_TAG",
	"DRW_TOKEN_FLOAT",
	"DRW_TOKEN_BEGINNING_OF_DICTIONARY",
	"DRW_TOKEN_END_OF_DICTIONARY",
	"DRW_TOKEN_BEGINNING_OF_LIST",
	"DRW_TOKEN_END_OF_LIST"
};

drwScanner::drwScanner(const string& path, drwLog& log):
	m_log(log),
	m_token(DRW_TOKEN_NONE){
	m_string[0] = 0;
	FILE* fd = fopen(path.c_str(), "rb");
	if(!fd) throw runtime_error(strerror(errno));
	int end = fseek(fd, SEEK_END, 0);
	if(end == -1) throw runtime_error(strerror(errno));
	int begin = fseek(fd, SEEK_SET, 0);
	if(begin == -1) throw runtime_error(strerror(errno));
	unsigned int size = end - begin;
	m_begin = new char [size];
	if(!m_begin) throw runtime_error("m_stream allocation failed");
	m_end = m_begin + size;
	m_pointer = m_begin;
	if(size != fread(m_begin, 1, size, fd))
		throw runtime_error("m_stream allocation failed");
	fclose(fd);
}


bool drwScanner::eof(void){
	return (m_end > m_pointer) ? false : true;
}

const char* drwScanner::tag(void){
	m_log << verbose << "m_token is " << token_string() << " as expected token is DRW_TOKEN_TAG" << eol;
	if (m_token != DRW_TOKEN_TAG) throw logic_error("Not a tag");
	return m_string;
}

drwToken drwScanner::scan(void){
	return DRW_TOKEN_NONE;
}

double drwScanner::floating_number(void){
	if (m_token != DRW_TOKEN_FLOAT) throw logic_error("Not a float");
	return m_float;
}

const char* drwScanner::token_string(void){
	if (m_token < DRW_TOKEN_NONE || m_token >= DRW_TOKEN_MAX) return "unknown";
	return s_token_sting[m_token];
}
