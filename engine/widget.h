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

#ifndef __DRW_WIDGET_H__
#define __DRW_WIDGET_H__

#include <string>
#include "engine_native.h"
#include "log.h"

using namespace std;

enum DRW_WIDGET_TYPE{
	DRW_WIDGET_TYPE_WINDOW = 0,
	DRW_WIDGET_TYPE_BUTTON
};

class drwWidget{
	protected:
		string m_id;
		drwLog& m_log;
		drwWidgetHandle* m_handle;
	public:
		const DRW_WIDGET_TYPE type;
		drwWidget(const DRW_WIDGET_TYPE wtype);
		virtual ~drwWidget();
		void id(const string& str_id);
		string& id(void);
		drwWidgetHandle* handle(void);
};
#endif //__DRW_WIDGET_H__
