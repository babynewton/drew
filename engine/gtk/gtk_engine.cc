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

#include "../engine.h"
#include "gtk_window.h"
#include "gtk_button.h"

static drwEngine* s_current = NULL;

drwWindow* drwEngine::new_window(void){
	return (drwWindow*)new drwGtkWindow;
}

drwButton* drwEngine::new_button(void){
	return new drwGtkButton;
}

drwEngine* drwEngine::current(void){
	return s_current;
}

drwEngine::drwEngine(int argc, char* argv[]):m_window(0), m_log(drwLog::instance()){
	gtk_init(&argc, &argv);
}

void drwEngine::add(drwWindow* window){
	m_window = window;
}

void drwEngine::run(void){
	s_current = this;
	gtk_main();
}

void drwEngine::quit(void){
	if(s_current == this) s_current = NULL;
	gtk_main_quit();
}

drwWindow* drwEngine::window(void){
	return m_window;
}
