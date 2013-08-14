#include "dml.h"
#include "parser/dml_parser.h"
#include "parser/scanner.h"

drwDml::drwDml():m_log(drwLog::instance()){
}

void drwDml::parse(drwEngine* engine, const string path){
	m_log << debug << "drwDmlPaser parses " << path << eol;
	drwScanner scanner(path);
	drwDmlParser parser;
	parser.parse(engine, scanner);
}
