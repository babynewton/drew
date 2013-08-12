#include <string>
#include "native_window.h"

using namespace std;

drwNativeWindow::drwNativeWindow():m_log(drwLog::instance()){}

void drwNativeWindow::add(drwButton* button){ }

void drwNativeWindow::set_border(int border){
	m_log << verbose << "drwNativeWindow::set_border(" << border << ")" << eol;
}
void drwNativeWindow::set_before_destroy_cb(string& cb){
	m_log << verbose << "drwNativeWindow::set_before_destroy_cb(" << cb << ")" << eol;
}

void drwNativeWindow::set_on_destroy_cb(string& cb){
	m_log << verbose << "drwNativeWindow::set_on_destroy_cb(" << cb << ")" << eol;
}

