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
#include <string.h>
#include "dml_parser.h"
#include "window_parser.h"
#include "../../config.h"

drwDmlParser::drwDmlParser(drwEngine* engine):m_log(drwLog::instance()), m_engine(engine){}

void drwDmlParser::parse(drwScanner& scanner){
	drwToken token = DRW_TOKEN_NONE;
	while(token = scanner.scan(), token != DRW_TOKEN_END_OF_FILE){
		string& symbol = scanner.symbol();
		if(symbol == "version"){
			token = scanner.scan();
			if(token != DRW_TOKEN_SEPARATOR) throw logic_error("Separator(:) is supposed to come");
			scanner.scan();
			if(DRW_DML_VERSION < scanner.floating_number()){
				stringstream ss;
				ss << "This DML(" << scanner.floating_number() << ") is later than the runner(" << DRW_DML_VERSION << ")";
				throw logic_error(ss.str());
			}
			m_log << verbose << "Version match : " << scanner.floating_number() << " vs " << DRW_DML_VERSION << eol;
		} else if (symbol == "window"){
			token = scanner.scan();
			if(token != DRW_TOKEN_BEGINNING_OF_DICTIONARY) {
				throw logic_error("window is not a dictionary");
			}
			drwWindowParser parser(m_engine);
			drwWindow* window = parser.parse(scanner);
			if(window) m_engine->top((drwWidget*)window);
		} else if(symbol == "_on_init"){
			token = scanner.scan(DRW_SCAN_POLICY_DICTIONARY_AS_CODE);
			if(token != DRW_TOKEN_CODE) {
				throw logic_error("_before_destroy has an invalid code");
			}
			m_engine->on_init_cb(scanner.code());
		} else {
			stringstream ss;
			ss << "invalid symbol : " << symbol;
			throw logic_error(ss.str());
		}
	}
	m_log << debug << "drwDmlParser::parse is over" << eol;
}
