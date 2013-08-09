#include <iostream>
#include "engine.h"
#include "dml.h"
#include "argument.h"

using namespace std;

int main(int argc, char* argv[]){
	drwArgument arg(argc, argv);
	drwDmlParser parser;
	drwEngine* engine = parser.parse(arg.path());
	engine->run();
	return 0;
}
