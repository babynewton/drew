#include <stdexcept>
#include <sstream>
#include <string.h>
#include "dml_parser.h"
#include "window_parser.h"

#define DRW_DML_VERSION 1.0

drwDmlParser::drwDmlParser():m_log(drwLog::instance()){}

drwEngine* drwDmlParser::parse(drwScanner& scanner){
	drwToken token = DRW_TOKEN_NONE;
	drwEngine* engine = new drwEngine;
	while(!scanner.eof()){
		scanner.scan();
		string& symbol = scanner.symbol();
		if(symbol == "version"){
			token = scanner.scan();
			if(token != DRW_TOKEN_SEPARATOR) throw logic_error("Separator(:) is supposed to come");
			scanner.scan();
			if(DRW_DML_VERSION < scanner.floating_number()){
				stringstream ss;
				ss << "This DML(" << scanner.floating_number() << ") is later than the runner(" << DRW_DML_VERSION << ")";
				delete engine;
				throw logic_error(ss.str());
			}
			m_log << verbose << "Version match : " << scanner.floating_number() << " vs " << DRW_DML_VERSION << eol;
		} else if (symbol == "window"){
			token = scanner.scan();
			if(token != DRW_TOKEN_BEGINNING_OF_DICTIONARY) {
				delete engine;
				throw logic_error("gui is not a dictionary");
			}
			drwWindowParser parser;
			drwWindow* window = parser.parse(scanner);
			if(window) engine->add(window);
			token = scanner.scan();
			if(token != DRW_TOKEN_END_OF_DICTIONARY) {
				delete engine;
				throw logic_error("gui does not end with a dictionary");
			}
		} else {
			stringstream ss;
			ss << "invalid symbol : " << symbol;
			delete engine;
			throw logic_error(ss.str());
		}
	}
}
