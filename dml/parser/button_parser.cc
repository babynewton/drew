#include <stdexcept>
#include <sstream>
#include "window_parser.h"
#include "button_parser.h"

#include "engine.h"

drwButtonParser::drwButtonParser():m_log(drwLog::instance()){}

drwButton* drwButtonParser::parse(drwScanner& scanner){
	drwButton* button = drwEngine::new_button();
	drwToken token = DRW_TOKEN_NONE;
	while(!scanner.eof()){
		scanner.scan();
		string& symbol = scanner.symbol();
		if(symbol == "label"){
		} else if(symbol == "on_click"){
		} else {
			stringstream ss;
			ss << "invalid symbol : " << symbol;
			delete button;
			throw logic_error(ss.str());
		}
	}
	return button;
}
