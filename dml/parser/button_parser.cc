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
		} else if(symbol == "_on_click"){
			token = scanner.scan(DRW_SCAN_POLICY_DICTIONARY_AS_CODE);
			if(token != DRW_TOKEN_CODE) {
				delete button;
				throw logic_error("_on_click has an invalid code");
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
