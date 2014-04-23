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

#include <stdexcept>
#include <sstream>
#include "lua_dthread.h"
#include "lua_button.h"
#include "lua_window.h"
#include "lua_box.h"
#include "lua_separator.h"
#include "lua_label.h"

drwLuaThread::drwLuaThread(lua_State* parent, drwWidget* widget):m_log(drwLog::instance()){
	m_runner = lua_newthread(parent);
	if(!m_runner) throw runtime_error("Creating the thread failed");
	switch(widget->type()){
		case DRW_WIDGET_TYPE_WINDOW:
			lua_window_as_this(m_runner, (drwWindow*)widget);
			break;
		case DRW_WIDGET_TYPE_BUTTON:
			lua_button_as_this(m_runner, (drwButton*)widget);
			break;
		case DRW_WIDGET_TYPE_LABEL:
			lua_label_as_this(m_runner, (drwLabel*)widget);
			break;
		case DRW_WIDGET_TYPE_HBOX:
		case DRW_WIDGET_TYPE_VBOX:
			lua_box_as_this(m_runner, (drwBox*)widget);
			break;
		case DRW_WIDGET_TYPE_HSEPARATOR:
			lua_hseparator_as_this(m_runner, (drwHSeparator*)widget);
			break;
		case DRW_WIDGET_TYPE_VSEPARATOR:
			lua_vseparator_as_this(m_runner, (drwVSeparator*)widget);
			break;
		default:
			{
				stringstream ss;
				ss << "unrecognized widget type" << widget->type_str();
				throw runtime_error(ss.str());
			}
			break;
	}
}

drwLuaThread::~drwLuaThread(){
//	lua_close(m_runner);
}

void drwLuaThread::failed(void){
	const char* err = lua_tostring(m_runner, -1);
	m_log << debug << err << eol;
	throw runtime_error(err);
}

bool drwLuaThread::run(const char* code){
	if (luaL_loadstring(m_runner, code)) failed();
	if(lua_resume(m_runner, 0)) failed();
	if(!lua_gettop(m_runner)) return true;
	if(!lua_isboolean(m_runner, -1)) throw runtime_error("Returned result is not a boolean");
	return (lua_toboolean(m_runner, -1)) ? true : false;
}
