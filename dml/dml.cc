#include "dml.h"
#include "parser/dml_parser.h"
#include "parser/scanner.h"

drwDml::drwDml():m_log(drwLog::instance()){
}

drwEngine* drwDml::parse(const string path){
	m_log << debug << "drwDmlPaser parses " << path << eol;
	drwScanner scanner(path);
	drwDmlParser parser;
	drwEngine* engine = parser.parse(scanner);
	return engine;
}
