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

#ifndef __DRW_HBOX_H__
#define __DRW_HBOX_H__

#include <string>
#include "widget.h"
#include "log.h"

using namespace std;

class drwHBox : public drwWidget{
	private:
		bool m_homogenous;
		int m_spacing;
		bool m_expand;
		bool m_fill;
		unsigned int m_padding;
	public:
		drwHBox();
		virtual ~drwHBox();
		void initialize(void);
		void add(drwWidget* widget);
		void homogenous(const bool bhomogenous);
		const bool homogenous(void);
		void spacing(const int lspacing);
		const int spacing(void);
		void expand(const bool bexpand);
		const bool expand(void);
		void fill(const bool bfill);
		const bool fill(void);
		void padding(const unsigned int ulpadding);
		const unsigned int padding(void);
};
#endif //__DRW_HBOX_H__
