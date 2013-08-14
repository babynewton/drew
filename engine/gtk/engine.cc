#include "../engine.h"
#include "gtk_window.h"
#include "gtk_button.h"

drwWindow* drwEngine::new_window(void){
	return new drwGtkWindow;
}

drwButton* drwEngine::new_button(void){
	return new drwGtkButton;
}

drwEngine::drwEngine(int argc, char* argv[]):m_window(0), m_log(drwLog::instance()){
	gtk_init(&argc, &argv);
}

void drwEngine::add(drwWindow* window){
	m_window = window;
}

void drwEngine::run(void){
	gtk_main();
}

void drwEngine::quit(void){
	gtk_main_quit();
}

drwWindow* drwEngine::window(void){
	return m_window;
}
