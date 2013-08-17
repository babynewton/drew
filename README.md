drew
====

Drew is a lightweight UI description language and its runner.

Why drew?
====

Drew's concept is similar to QML.

However, drew has simpler grammar than QML, lighter than Javascript, and, much cheaper than QT.

QML is a combination of Javascript, QML language, and QT.

Drew is a combination of Lua script, DML language, and GTK.

install
====


./configure

make

sudo make install

If you want to create the debian package, do as follows

make deb

run
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
Following form is a description of DML in e-BNF.

INTEGER := [0-9]+

FLOATING := IEEE759 floating point

SCRIPT := {*}

STRING := ".*"


DML := version_sentence gui_sentence

version_sentence := version : FLOATING

gui_sentence := window_sentence

window_sentence := window { window_content }

window_content := border : INTEGER | _on_destroy SCRIPT | _before_destroy SCRIPT | button_sentence

button_sentence := button { button_content }

button_content := label : STRING | _on_click SCRIPT

The hello world example of DML
====

#!/usr/local/bin/drew

version:1.0

window{
	border:10
	before_destroy{
		log.verbose("delete-devent occurred")
		return false
	}
	on_destroy{
		log.debug("quit")
		gui.quit()
	}
	button{
		label:"hello world"
		on_click{
			cout.print("hello world!")
		}
	}
}

script extension
====

gui
=====

quit : quit the DML application

log
=====

verbose : log verbose message on cerr. It works only when drew is executed with -v or --verbose argument

debug : log debug message on cerr. It works only when drew is executed with -d or --debug argument

cout
=====

print : print the arguments to cout.

License
====

Drew is under MIT license.

Thanks to
====

Drew Scheneman, my first English teacher who taught me English in English
