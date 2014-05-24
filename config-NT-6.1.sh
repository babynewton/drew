#!/bin/bash

PACKAGE_EXTENSION=exe
PACKAGE_FORMAT=msi

INST_BIN=/
INST_LIB=/
INST_DOC=/
INST_EXAMPLE=/examples

CORES=$NUMBER_OF_PROCESSORS

function init_luajit(){
	LUA_DIRECTORY=LuaJIT-2.0.3
	LUA_ARCHIVE=$LUA_DIRECTORY.tar.gz
	wget http://luajit.org/download/$LUA_ARCHIVE
	tar -zxvf $LUA_ARCHIVE dependents/luajit
	rm $LUA_ARCHIVE
	sed "s#@dir@#$LUA_DIRECTORY" < dependents/lua/$MK.in > dependents/lua/$MK
	SCRIPT_INCS="dependents/lua/$LUA_DIRECTORY/src"
	SCRIPT_LIBS="-Ldependents/lua/$LUA_DIRECTORY/src -llua"
}

function init_lua(){
	LUA_DIRECTORY=lua-5.1.5
	LUA_ARCHIVE=$LUA_DIRECTORY.tar.gz
	wget http://www.lua.org/ftp/$LUA_ARCHIVE
	tar -zxvf $LUA_ARCHIVE dependents/lua
	rm $LUA_ARCHIVE
	sed "s#@dir@#$LUA_DIRECTORY#g;
		s#@root@#$PREFIX#g;
		s#@lib@#$INST_LIB#g;
		" < dependents/luajit/$MK.in > dependents/luajit/$MK
	SCRIPT_INCS="dependents/luajit/$LUA_DIRECTORY/src"
	SCRIPT_LIBS="-Ldependents/lua/$LUA_DIRECTORY/src -lluajit"
}

function init_gtk(){
	cp $DEPENDENTS_PATH/gtk/$MK.in $DEPENDENTS_PATH/gtk/$MK
}

function config_package(){
	cp toolbox/msi/$MK_IN toolbox/msi/$MK
}
