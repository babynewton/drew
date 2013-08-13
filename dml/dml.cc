#include "dml.h"
#include "parser/dml_parser.h"
#include "parser/scanner.h"

drwDml::drwDml():m_log(drwLog::instance()){
}

drwEngine* drwDml::parse(const string path, int argc, char* argv[]){
	m_log << debug << "drwDmlPaser parses " << path << eol;
	drwEngine* engine = new drwEngine(argc, argv);
	drwScanner scanner(path);
	drwDmlParser parser;
	parser.parse(engine, scanner);
	return engine;
}
