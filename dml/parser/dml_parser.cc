#include <stdexcept>
#include <sstream>
#include <string.h>
#include "dml_parser.h"

drwDmlParser::drwDmlParser(drwLog& log): m_log(log){ }

void drwDmlParser::parse(drwEngine* engine, drwScanner& scanner){
	while(scanner.eof()){
		drwToken token = scanner.scan();
		if(token != DRW_TOKEN_TAG) throw logic_error("invalid tag");
		const char* tag = scanner.tag();
		if(!strcmp(tag, "version")){
			token = scanner.scan();
			if(token != DRW_TOKEN_FLOAT) logic_error("version is not a float");
		} else if (!strcmp(tag, "gui")){
			token = scanner.scan();
			if(token != DRW_TOKEN_DICTIONARY) logic_error("gui is not a dictionary");
		} else {
			stringstream ss;
			ss << "invalid tag : " << tag;
			logic_error(ss.str());
		}
	}
}
