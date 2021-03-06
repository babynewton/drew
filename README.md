drew v0.2
====

Drew is an implementation of DML language specification.

DML is a lightweight UI description language.

Why drew?
====

Drew's basic idea is similar to QML.

However, drew has simpler grammar than QML, lighter than Javascript, and, much cheaper than QT.

QML is a combination of Javascript, QML language, and QT.

Drew is a combination of Lua script, DML language, and GTK.

How to install
====


./configure

make

sudo make install

If you want to create the debian package, do as follows

make deb

How to run
====

example/hello.drew

or 

drew example/hello.drew


If you want to see the debug messages, do as follows

example/hello.drew -d

or 

drew example/hello.drew -d


If you want to see the debug messages and verbose messages, do as follows

example/hello.drew -v

or 

drew example/hello.drew -v


If you want to see the help screen, do as follows

drew -h

or

drew --help

DML
====

DML(Drew Meta Language) is a UI description language. 

##Basic Grammar

Following form is a description of DML in e-BNF.

INTEGER := [0-9]+

FLOATING := IEEE759 floating point

CODE := '{' [ . | \n ]* '}'

STRING := ".*"

SYMBOL := [._]*

BOOL := true | false

VALUE := BOOL | STRING | FLOATING | INTEGER

TUPLE := SYMBOL ':' VALUE

LIST := SYMBOL '[' VALUE* ']'

SCRIPT := SYMBOL '(' SYMBOL* ')' CODE

DICTIONARY := SYMBOL '{' [ TUPLE | LIST | DICTIONARY ]* '}'

##UI Grammar

DML := meta_sentence gui_sentence

meta_sentence := version ':' FLOATING | profile ':' STRING

gui_sentence := '_on_init' window_sentence

window_sentence := window { window_content }

window_content := border : INTEGER | _on_destroy SCRIPT | _before_destroy SCRIPT | button_sentence

button_sentence := button { button_content }

button_content := label : STRING | _on_click SCRIPT

####The hello world example

	#!/usr/local/bin/drew
	version:0.1
	profile:"dml"
	window{
		border:10
		_before_destroy(){
			log.verbose("delete-devent occurred")
			return false
		}
		_on_destroy(){
			log.debug("quit")
			gui.quit()
		}
		button{
			label:"hello world"
			_on_click(){
				cout.print("hello world!")
			}
		}
	}

##UI elements

####window

The window sentence represents the window widget in the graphic widget library.

border(property) : sets the thickness of the window.

_before_destroy : is called before the window is closed. if it returns true, the winodw will not close. Otherwise, it closes.

_on_destroy : is called when the window is closed.

####button

The button sentence represents the button widget in the graphic widget library.

label : sets the caption of the button.

_on_click : is called when the button is clicked.


##script extensions

####gui

quit : quit the DML application

####log

verbose : log verbose message on cerr. It works only when drew is executed with -v or --verbose argument

debug : log debug message on cerr. It works only when drew is executed with -d or --debug argument

####cout

print : print the arguments to cout.

License
====

Drew is under MIT license.

Thanks to
====

Drew Scheneman, my first English teacher who taught me English in English
