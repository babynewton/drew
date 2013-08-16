/*
The MIT License (MIT)

Copyright (c) 2013 drew

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
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.#include <stdexcept>
*/

#include <iostream>
#include "engine.h"
#include "dml.h"
#include "argument.h"
#include "log.h"
#include "runtime_storage.h"

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
	drwRuntimeStorage::engine(engine);
	engine->run();
	delete engine;
	return 0;
}
