#include <iostream>
#include "engine.h"
#include "dml.h"
#include "argument.h"
#include "log.h"

using namespace std;

int main(int argc, char* argv[]){
	drwArgument arg(argc, argv);
	drwLog::enable(arg.verbose());
	drwDmlParser parser;
	drwEngine* engine = parser.parse(arg.path());
	engine->run();
	delete engine;
	return 0;
}
