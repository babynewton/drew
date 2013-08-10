#include "dml.h"
#include "parser/dml_parser.h"
#include "parser/scanner.h"

drwDml::drwDml(const bool onoff):m_log(onoff){
}

drwEngine* drwDml::parse(const string path){
	drwEngine* engine = new drwEngine;
	m_log << verbose << "drwDmlPaser parses " << path << eol;
	drwScanner scanner(path, m_log);
	drwDmlParser parser(m_log);
	parser.parse(engine, scanner);
	return engine;
}
