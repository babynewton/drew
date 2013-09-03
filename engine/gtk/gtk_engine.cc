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
#include <sstream>
#include <stdexcept>

static drwEngine* s_current = NULL;

drwEngine* drwEngine::current(void){
	return s_current;
}

drwEngine::drwEngine(int argc, char* argv[]):m_top(0), m_log(drwLog::instance()){
	gtk_init(&argc, &argv);
}

void drwEngine::top(drwWidget* widget){
	m_top = widget;
}

void drwEngine::run(void){
	s_current = this;
	if(m_on_init_cb.size()) m_runtime.run(m_on_init_cb.c_str());
	gtk_main();
}

void drwEngine::quit(void){
	if(s_current == this) s_current = NULL;
	gtk_main_quit();
}

drwWidget* drwEngine::top(void){
	return m_top;
}

drwWidget* drwEngine::cache(string& wid){
	if(m_cache.find(wid) == m_cache.end()){
		stringstream ss;
		ss << wid << " not found";
		throw runtime_error(ss.str());
	}
	m_log << verbose << "return m_cache[" << wid << "]" << eol;
	return m_cache[wid];
}

void drwEngine::cache(drwWidget* widget){
	string& wid = widget->id();
	if(m_cache.find(wid) != m_cache.end()){
		stringstream ss;
		ss << widget->id() << " already exist";
		throw runtime_error(ss.str());
	}
	m_log << verbose << "m_cache[" << wid << "] << drwWidget*" << eol;
	m_cache[wid] = widget;
}

void drwEngine::on_init_cb(string& code){
	m_log << verbose << "drwEngine::on_init_cb(" << code << ")" << eol;
	m_on_init_cb = code;
}

string drwEngine::on_init_cb(void){
	return m_on_init_cb;
}

drwThread* drwEngine::thread(drwWidget* widget){
	m_runtime.thread(widget);
}
