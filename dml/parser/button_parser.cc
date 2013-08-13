#include <stdexcept>
#include <sstream>
#include "window_parser.h"
#include "button_parser.h"

#include "engine.h"

drwButtonParser::drwButtonParser():m_log(drwLog::instance()){}

drwButton* drwButtonParser::parse(drwScanner& scanner){
	drwButton* button = drwEngine::new_button();
	drwToken token = DRW_TOKEN_NONE;
	while(token = scanner.scan(), token != DRW_TOKEN_END_OF_DICTIONARY){
		string& symbol = scanner.symbol();
		if(symbol == "label"){
			token = scanner.scan();
			if(token != DRW_TOKEN_SEPARATOR) {
				delete button;
				throw logic_error("Separator(:) is supposed to come");
			}
			scanner.scan();
			button->label(scanner.text());
		} else if(symbol == "on_click"){
			token = scanner.scan(DRW_SCAN_POLICY_DICTIONARY_AS_CODE);
			if(token != DRW_TOKEN_CODE) {
				delete button;
				throw logic_error("on_click has an invalid code");
			}
			button->click_cb(scanner.code());
		} else {
			stringstream ss;
			ss << "invalid symbol : " << symbol;
			delete button;
			throw logic_error(ss.str());
		}
	}
	m_log << debug << "drwButtonParser::parse is over" << eol;
	return button;
}
