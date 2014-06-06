#!/bin/bash

PREFIX=/usr/local

PACKAGE_EXTENSION=deb
PACKAGE_FORMAT=debian
PACKAGE_DEPENDS="libc6(>=2.15)"

INST_BIN=/bin
INST_DOC=/share/doc/$PACKAGE_NAME
INST_MAN1=/share/man/man1
INST_EXAMPLE=/share/$PACKAGE_NAME

DLL_EXT=".so"

CORES=`cat /proc/cpuinfo | grep processor | wc -l`

function init_luajit(){
	SCRIPT_INCS=`pkg-config --cflags luajit`
	if [ ! -n "$SCRIPT_INCS" ]
	then
		sudo apt-get install libluajit-5.1.dev
		SCRIPT_INCS=`pkg-config --cflags luajit`
	fi
	test "$VERBOSE" == false || echo luajit includes : $SCRIPT_INCS
	SCRIPT_LIBS=`pkg-config --libs luajit`
	test "$VERBOSE" == false || echo luajit libraries : $SCRIPT_LIBS
	PACKAGE_DEPENDS+=",libluajit-5.1-2"
}

function init_lua(){
	SCRIPT_INCS=`pkg-config --cflags lua5.1`
	if [ ! -n "$SCRIPT_INCS" ]
	then
		sudo apt-get install liblua5.1-0.dev
		SCRIPT_INCS=`pkg-config --cflags luajit`
	fi
	test "$VERBOSE" == false || echo lua includes : $SCRIPT_INCS
	SCRIPT_LIBS=`pkg-config --libs lua5.1`
	test "$VERBOSE" == false || echo lua libraries : $SCRIPT_LIBS
	PACKAGE_DEPENDS+=",liblua5.1-0"
}

function init_gtk(){
	UI_INCS=`pkg-config --cflags gtk+-2.0`
	if [ ! -n "$UI_INCS" ]
	then
		sudo apt-get install libgtk2.0-dev
		UI_INCS=`pkg-config --cflags gtk+-2.0`
	fi
	test "$VERBOSE" == false || echo gtk includes : $UI_INCS
	UI_LIBS=`pkg-config --libs gtk+-2.0`
	test "$VERBOSE" == false || echo gtk libraries : $UI_LIBS
	PACKAGE_DEPENDS+=",libgtk2.0-0"
}

function config_package(){
	test -n "which help2man" || sudo apt-get install help2man
	test $VERBOSE == false || echo Dependents:$PACKAGE_DEPENDS
	sed "s#@package@#$PACKAGE_NAME#g;
		s#@version@#$PACKAGE_VERSION#g;
		s#@arch@#$HOST_ARCH#g;
		s#@depends@#$PACKAGE_DEPENDS#g;
		s#@debian_package@#$PWD/$DIST_PACKAGE#g;
		s#@build_root@#$PWD#g;
		s#@root@#$PREFIX#g;
		s#@bin@#$INST_BIN#g;
		s#@doc@#$INST_DOC#g;
		s#@man1@#$INST_MAN1#g;
		s#@pkg_root@#$PWD$PACKAGE_ROOT_DIR#g;" < toolbox/debian/$MK_IN > toolbox/debian/$MK
	echo "toolbox/debian:$MK_IN ==> $MK"
}


