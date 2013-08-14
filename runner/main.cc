#include <iostream>
#include "engine.h"
#include "dml.h"
#include "argument.h"
#include "log.h"
#include "lua_runtime.h"

using namespace std;

int main(int argc, char* argv[]){
	drwArgument arg(argc, argv);
	drwLog::initialize(arg.log_level());
	drwDml dml;
	drwEngine* engine = new drwEngine(argc, argv);
	try {
		dml.parse(engine, arg.path());
	} catch (exception& e){
		cerr << "[error] " << e.what() << endl;
		return 0;
	}
	drwLuaRuntime::engine(engine);
	engine->run();
	delete engine;
	return 0;
}
