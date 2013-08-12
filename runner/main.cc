#include <iostream>
#include "engine.h"
#include "dml.h"
#include "argument.h"
#include "log.h"

using namespace std;

int main(int argc, char* argv[]){
	drwArgument arg(argc, argv);
	drwLog::initialize(arg.log_level());
	drwDml dml;
	drwEngine* engine = NULL;
	try {
		engine = dml.parse(arg.path());
	} catch (exception& e){
		cerr << "[error] " << e.what() << endl;
	}
	engine->run();
	delete engine;
	return 0;
}
