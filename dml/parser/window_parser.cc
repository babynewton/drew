/*
The MIT License (MIT)

Copyright (c) 2013 drew

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

drwWindowParser::drwWindowParser():m_log(drwLog::instance()){}

drwWindow* drwWindowParser::parse(drwScanner& scanner){
	drwWindow* window = drwEngine::new_window();
	drwToken token = DRW_TOKEN_NONE;
	while(token = scanner.scan(), token != DRW_TOKEN_END_OF_DICTIONARY){
		string& symbol = scanner.symbol();
		if(symbol == "border"){
			token = scanner.scan();
			if(token != DRW_TOKEN_SEPARATOR) {
				delete window;
				throw logic_error("Separator(:) is supposed to come");
			}
			scanner.scan();
			window->border(scanner.integer_number());
		} else if(symbol == "before_destroy"){
			token = scanner.scan(DRW_SCAN_POLICY_DICTIONARY_AS_CODE);
			if(token != DRW_TOKEN_CODE) {
				delete window;
				throw logic_error("before_destroy has an invalid code");
			}
			window->before_destroy_cb(scanner.code());
		} else if(symbol == "on_destroy"){
			token = scanner.scan(DRW_SCAN_POLICY_DICTIONARY_AS_CODE);
			if(token != DRW_TOKEN_CODE) {
				delete window;
				throw logic_error("on_destroy has an invalid code");
			}
			window->on_destroy_cb(scanner.code());
		} else if(symbol == "button"){
			token = scanner.scan();
			if(token != DRW_TOKEN_BEGINNING_OF_DICTIONARY) {
				delete window;
				throw logic_error("button is not a dictionary");
			}
			drwButtonParser parser;
			drwButton* button = parser.parse(scanner);
			window->to_widget()->add(button->to_widget());
		} else {
			stringstream ss;
			ss << "invalid symbol : " << symbol;
			delete window;
			throw logic_error(ss.str());
		}
	}
	m_log << debug << "drwWindowParser::parse is over" << eol;
	return window;
}
