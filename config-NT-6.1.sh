#!/bin/bash

PACKAGE_EXTENSION=exe
PACKAGE_FORMAT=msi

INST_BIN=/
INST_LIB=/
INST_DOC=/
INST_EXAMPLE=/examples

CORES=$NUMBER_OF_PROCESSORS

MK=Makefile

function init_luajit(){
	LUA_DIRECTORY=LuaJIT-2.0.3
	if [ ! -d "dependents/luajit/$LUA_DIRECTORY" ]
	then
		LUA_ARCHIVE=$LUA_DIRECTORY.tar.gz
		test -f $LUA_ARCHIVE || wget http://luajit.org/download/$LUA_ARCHIVE
		tar -zxvf $LUA_ARCHIVE -C dependents/luajit
		rm $LUA_ARCHIVE
	fi
	SCRIPT_INCS="dependents/luajit/$LUA_DIRECTORY/src"
	SCRIPT_LIBS="-Ldependents/luajit/$LUA_DIRECTORY/src -llua"
	sed "s#@dir@#$LUA_DIRECTORY#g;
		s#@root@#$PREFIX#g;
		s#@lib@#$INST_LIB#g;
		" < dependents/luajit/$MK.in > dependents/luajit/$MK
}

function init_lua(){
	LUA_DIRECTORY=lua-5.1.5
	if [ ! -d "dependents/lua/$LUA_DIRECTORY" ]
	then
		LUA_ARCHIVE=$LUA_DIRECTORY.tar.gz
		test -f $LUA_ARCHIVE || wget http://www.lua.org/ftp/$LUA_ARCHIVE
		tar -zxvf $LUA_ARCHIVE -C dependents/luajit
		rm $LUA_ARCHIVE
	fi
	SCRIPT_INCS="dependents/lua/$LUA_DIRECTORY/src"
	SCRIPT_LIBS="-Ldependents/lua/$LUA_DIRECTORY/src -lluajit"
	sed "s#@dir@#$LUA_DIRECTORY#g" < dependents/lua/$MK.in > dependents/lua/$MK
}

function init_gtk(){
	cp dependents/gtk/$MK.in dependents/gtk/$MK
}

function config_package(){
	cp toolbox/msi/$MK_IN toolbox/msi/$MK
}
