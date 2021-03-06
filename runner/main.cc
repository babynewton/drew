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
#include "argument.h"
#include "log.h"
#include "../config.h"

using namespace std;

void show_banner(void){
	cout << DRW_NAME << " " << DRW_VERSION << " " << endl;// << DRW_HOST_ARCH << endl;
	cout << "Copyright(C) 2013 Newton.Kim(babynewton73@gmail.com)" << endl;
	cout << "License MIT: The MIT License (MIT) <http://opensource.org/licenses/MIT>" << endl;
}

void show_help(void){
	cout << "Usage: drew [OPTION]... file" << endl;
	cout << endl;
	cout << "Options:" << endl;
	cout << "  -v, --verbose  show verbose message(for debugging)" << endl;
	cout << "  --version      shows verversion" << endl;
	cout << "  -d, --debug    show debug message(for debugging)" << endl;
	cout << "  -h, --help     show help screen(this screen)" << endl;
	cout << endl;
}

void show_version(void){
	cout << DRW_NAME << " " << DRW_VERSION << endl;
}

int main(int argc, char* argv[]){
	drwArgument arg(argc, argv);
	if(arg.banner()) show_banner();
	if(arg.help()) {
		if(!arg.banner()) {
			show_banner();
			cout << endl;
		}
		show_help();
		return 0;
	}
	if(arg.version()){
		show_version();
		return 0;
	}
	drwLog::initialize(arg.log_level());
	drwEngine* engine = drwEngine::instance();
	engine->initialize(argc, argv);
	try {
		engine->parse(arg.path(), arg.arguments());
	} catch (exception& e){
		cerr << "[error] " << e.what() << endl;
		return 1;
	}
	engine->run();
	return 0;
}
