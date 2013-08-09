#include "dml.h"

drwDmlParser::drwDmlParser(const bool onoff):m_log(onoff){
}

drwEngine* drwDmlParser::parse(const string path){
	drwEngine* engine = new drwEngine;
	m_log << "drwDmlPaser parses " << path << endl;
	return engine;
}
