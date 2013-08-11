#include <stdexcept>
#include <sstream>
#include <string.h>
#include "dml_parser.h"

#define DRW_DML_VERSION 1.0

drwDmlParser::drwDmlParser(drwLog& log): m_log(log){ }

void drwDmlParser::parse(drwEngine* engine, drwScanner& scanner){
	string tag;
	drwToken token = DRW_TOKEN_NONE;
	while(scanner.eof()){
		scanner.scan();
		const char* tag = scanner.tag();
		if(!strcmp(tag, "version")){
			scanner.scan();
			if(DRW_DML_VERSION < scanner.floating_number()){
				stringstream ss;
				ss << "This DML(" << scanner.floating_number() << ") is later than the runner(" << DRW_DML_VERSION << ")";
				throw logic_error(ss.str());
			}
		} else if (!strcmp(tag, "gui")){
			token = scanner.scan();
			if(token != DRW_TOKEN_BEGINNING_OF_DICTIONARY) logic_error("gui is not a dictionary");
		} else {
			stringstream ss;
			ss << "invalid tag : " << tag;
			throw logic_error(ss.str());
		}
	}
}
