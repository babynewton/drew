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

#include <gtk/gtk.h>
#include "box.h"

using namespace std;

drwBox::drwBox() : drwWidget(),
	m_expand(true),
	m_fill(true),
	m_padding(0)
{
}

drwBox::drwBox(drwBox* box) : drwWidget(box),
	m_expand(box->m_expand),
	m_fill(box->m_fill),
	m_padding(box->m_padding)
{
}

drwBox::~drwBox(){ }

void drwBox::add(drwWidget* wgt){
	gtk_box_pack_start(GTK_BOX(m_handle), GTK_WIDGET(wgt->handle()), m_expand, m_fill, 0);
}

void drwBox::homogeneous(const bool bhomogeneous){
	gtk_box_set_homogeneous(GTK_BOX(m_handle), (gboolean)bhomogeneous);
}

const bool drwBox::homogeneous(void){
	return gtk_box_get_homogeneous(GTK_BOX(m_handle));
}

void drwBox::spacing(const int lspacing){
	gtk_box_set_spacing(GTK_BOX(m_handle), lspacing);
}

const int drwBox::spacing(void){
	return gtk_box_get_spacing(GTK_BOX(m_handle));
}

void drwBox::expand(const bool bexpand){
	m_expand = bexpand;
}

const bool drwBox::expand(void){
	return m_expand;
}

void drwBox::fill(const bool bfill){
	m_fill = bfill;
}

const bool drwBox::fill(void){
	return m_fill;
}

void drwBox::padding(const unsigned int ulpadding){
	m_padding = ulpadding;
}

const unsigned int drwBox::padding(void){
	return m_padding;
}
