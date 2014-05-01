#!/bin/bash

PACKAGE_DEPENDS="libgtk2.0-0"
PACKAGE_EXTENSION=deb

PACKAGE_DEPENDS_LUA=liblua5.1-0
PACKAGE_DEPENDS_LUAJIT=libluajit5.1-2


function config_tools(){
	DEVS="liblua5.1-0-dev libluajit-5.1-dev libgtk2.0-dev"
	for DEV in $DEVS
	do
		echo installing $DEV
		sudo apt-get install $DEV
	done
}

