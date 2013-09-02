/*
The MIT License (MIT)

Copyright (c) 2013 Newton Kim

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
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <iostream>
#include "engine.h"
#include "dml.h"
#include "argument.h"
#include "log.h"
#include "../config.h"

using namespace std;

void show_banner(void){
	cout << DRW_NAME << " v" << DRW_VERSION << " " << DRW_HOST_ARCH << endl;
	cout << "The MIT License (MIT)" << endl;
	cout << "Copyright(C) 2013 Newton.Kim(babynewton73@gmail.com)" << endl;
}

void show_help(void){
	cout << "Usage: drew file [options]" << endl;
	cout << endl;
	cout << "-v, --verbose\t" << "show verbose message(for debugging)" << endl;
	cout << "-d, --debug\t" << "show debug message(for debugging)" << endl;
	cout << "-h, --help\t" << "show help screen(this screen)" << endl;
	cout << endl;
}

int main(int argc, char* argv[]){
	drwArgument arg(argc, argv);
	if(arg.banner()) show_banner();
	if(arg.help()) {
		if(!arg.banner()) show_banner();
		show_help();
		return 0;
	}
	drwLog::initialize(arg.log_level());
	drwDml dml;
	drwEngine* engine = new drwEngine(argc, argv);
	try {
		dml.parse(engine, arg.path());
	} catch (exception& e){
		cerr << "[error] " << e.what() << endl;
		delete engine;
		return 1;
	}
	engine->run();
	delete engine;
	return 0;
}
