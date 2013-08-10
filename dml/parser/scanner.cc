#include "scanner.h"

drwScanner::drwScanner(drwScanner& scanner):m_log(scanner.m_log){}

drwScanner::drwScanner(const string& path, drwLog& log):
	m_log(log){}


bool drwScanner::eof(void){
	return false;
}

const char* drwScanner::tag(void){
}

drwToken drwScanner::scan(void){
	return DRW_TOKEN_NONE;
}
