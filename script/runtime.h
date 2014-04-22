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

#ifndef __DRW_RUNTIME_H__
#define __DRW_RUNTIME_H__

#include <vector>
#include <string>
#include "widget.h"

class drwRuntime{
	public:
		virtual ~drwRuntime(){};
		static drwRuntime* instance(void);
		virtual void initialize(const string& code, vector<string>& arguments) = 0;
		virtual bool run(drwWidget* widget, const unsigned long index) = 0;
		virtual bool run(drwWidget* widget, const string& code) = 0;
		virtual const unsigned long script(unsigned long uid, const string& code) = 0;
};

#endif //__DRW_RUNTIME_H__
