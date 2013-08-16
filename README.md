drew
====

Drew is a lightweight UI description language and its runner.

Why drew?
====

Drew's concept is similar to QML.

However, drew has simpler grammar than QML, lighter than Javascript, and, much cheaper than QT.

QML is a combination of Javascript, QML language, and QT.

Drew is a combination of Lua script, DML language, and GTK.

License
====

Drew is under MIT license.

DML
====

DML(Drew Meta Language) is a UI description language

INTEGER = [0-9]+

FLOATING = IEEE759 floating point

SCRIPT = {*}

STRING = ".*"


DML <- version_sentence gui_sentence

version_sentence <- version : FLOATING

gui_sentence <- window_sentence

window_sentence <- window { window_content }

window_content <- border : INTEGER | on_destroy SCRIPT | before_destroy SCRIPT | button_sentence

button_sentence <- button { button_content }

button_content <- label : STRING | on_click SCRIPT

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

install
====


./configure

make

sudo make install

make deb

run
====

example/hello.drew

or 

drew example/hello.drew

Thanks to
====

Drew Scheneman, my first English teacher who taught me English in English
