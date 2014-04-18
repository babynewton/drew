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
#include "hbox.h"

using namespace std;

drwHBox::drwHBox() : drwWidget(),
	m_homogenous(false),
	m_spacing(0),
	m_expand(true),
	m_fill(true),
	m_padding(0)
{
}

drwHBox::~drwHBox(){ }

void drwHBox::initialize(void){
	m_handle = gtk_hbox_new(m_homogenous, m_spacing);
	gtk_widget_show(GTK_WIDGET(m_handle));
}

void drwHBox::add(drwWidget* wgt){
	if(!m_handle) initialize();
	gtk_box_pack_start(GTK_BOX(m_handle), GTK_WIDGET(wgt->handle()), m_expand, m_fill, 0);
}

void drwHBox::homogenous(const bool bhomogenous){
	m_homogenous = bhomogenous;
}

void drwHBox::spacing(const int lspacing){
	m_spacing = lspacing;
}

void drwHBox::expand(const bool bexpand){
	m_expand = bexpand;
}

void drwHBox::fill(const bool bfill){
	m_fill = bfill;
}

void drwHBox::padding(const unsigned int ulpadding){
	m_padding = ulpadding;
}

