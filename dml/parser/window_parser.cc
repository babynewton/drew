#include <stdexcept>
#include <sstream>
#include "window_parser.h"
#include "button_parser.h"

#include "engine.h"

drwWindowParser::drwWindowParser():m_log(drwLog::instance()){}

drwWindow* drwWindowParser::parse(drwScanner& scanner){
	drwWindow* window = drwEngine::new_window();
	drwToken token = DRW_TOKEN_NONE;
	while(!scanner.eof()){
		scanner.scan();
		string& symbol = scanner.symbol();
		if(symbol == "border"){
			token = scanner.scan();
			if(token != DRW_TOKEN_SEPARATOR) {
				delete window;
				throw logic_error("Separator(:) is supposed to come");
			}
			scanner.scan();
			window->set_border(scanner.integer_number());
		} else if(symbol == "before_destroy"){
			token = scanner.scan(DRW_SCAN_POLICY_DICTIONARY_AS_CODE);
			if(token != DRW_TOKEN_CODE) {
				delete window;
				throw logic_error("before_destroy has an invalid code");
			}
			window->set_before_destroy_cb(scanner.code());
		} else if(symbol == "on_destroy"){
			token = scanner.scan(DRW_SCAN_POLICY_DICTIONARY_AS_CODE);
			if(token != DRW_TOKEN_CODE) {
				delete window;
				throw logic_error("on_destroy has an invalid code");
			}
			window->set_on_destroy_cb(scanner.code());
		} else if(symbol == "button"){
			token = scanner.scan();
			if(token != DRW_TOKEN_BEGINNING_OF_DICTIONARY) {
				delete window;
				throw logic_error("button is not a dictionary");
			}
			drwButtonParser parser;
			drwButton* button = parser.parse(scanner);
			window->add(button);
			token = scanner.scan();
			if(token != DRW_TOKEN_END_OF_DICTIONARY) {
				delete window;
				throw logic_error("button does not end with a dictionary");
			}
		} else {
			stringstream ss;
			ss << "invalid symbol : " << symbol;
			delete window;
			throw logic_error(ss.str());
		}
	}
	return window;
}
