#!/bin/bash

PACKAGE_EXTENSION=exe
PACKAGE_FORMAT=msi

INST_BIN=/
INST_LIB=/
INST_DOC=/
INST_EXAMPLE=/examples

EXE_EXT=".exe"
DLL_EXT=".dll"

#CORES=$NUMBER_OF_PROCESSORS
CORES=1

MK=Makefile

function init_luajit(){
	LUA_DIRECTORY=LuaJIT-2.0.3
	if [ ! -d "dependents/luajit/$LUA_DIRECTORY" ]
	then
		LUA_ARCHIVE=$LUA_DIRECTORY.tar.gz
		test -f $LUA_ARCHIVE || wget http://luajit.org/download/$LUA_ARCHIVE
		tar -zxvf $LUA_ARCHIVE -C dependents/luajit
	fi
	SCRIPT_INCS="-I$PWD/dependents/luajit/$LUA_DIRECTORY/src"
	SCRIPT_LIBS="-L$PWD/dependents/luajit/$LUA_DIRECTORY/src -llua51"
	sed "s#@dir@#$LUA_DIRECTORY#g;
		s#@root@#$PREFIX#g;
		s#@lib@#$INST_LIB#g;
		s#@dll_ext@#$DLL_EXT#g;
		" < dependents/luajit/$MK.in > dependents/luajit/$MK
}

function init_lua(){
	LUA_DIRECTORY=lua-5.1.5
	if [ ! -d "dependents/lua/$LUA_DIRECTORY" ]
	then
		LUA_ARCHIVE=$LUA_DIRECTORY.tar.gz
		test -f $LUA_ARCHIVE || wget http://www.lua.org/ftp/$LUA_ARCHIVE
		tar -zxvf $LUA_ARCHIVE -C dependents/lua
	fi
	SCRIPT_INCS="-I$PWD/dependents/lua/$LUA_DIRECTORY/src"
	SCRIPT_LIBS="-L$PWD/dependents/lua/$LUA_DIRECTORY/src -llua"
	sed "s#@dir@#$LUA_DIRECTORY#g
		s#@root@#$PREFIX#g;
		s#@lib@#$INST_LIB#g;
		s#@dll_ext@#$DLL_EXT#g;
		" < dependents/lua/$MK.in > dependents/lua/$MK
}

function init_gtk(){
	GTK_DIRECTORY=gtk+-bundle_2.24.10-20120208_win32
	if [ ! -d "dependents/gtk/$GTK_DIRECTORY" ]
	then
		GTK_ARCHIVE=$GTK_DIRECTORY.zip
		test -f $GTK_ARCHIVE || wget http://ftp.gnome.org/pub/gnome/binaries/win32/gtk+/2.24/$GTK_ARCHIVE
		unzip $GTK_ARCHIVE -d dependents/gtk/$GTK_DIRECTORY
	fi
	UI_INCS="-I$PWD/dependents/gtk/$GTK_DIRECTORY/include/gtk-2.0"
	UI_INCS+=" -I$PWD/dependents/gtk/$GTK_DIRECTORY/include/glib-2.0"
	UI_INCS+=" -I$PWD/dependents/gtk/$GTK_DIRECTORY/include/cairo"
	UI_INCS+=" -I$PWD/dependents/gtk/$GTK_DIRECTORY/include/pango-1.0"
	UI_INCS+=" -I$PWD/dependents/gtk/$GTK_DIRECTORY/include/gdk-pixbuf-2.0"
	UI_INCS+=" -I$PWD/dependents/gtk/$GTK_DIRECTORY/include/atk-1.0"
	UI_INCS+=" -I$PWD/dependents/gtk/$GTK_DIRECTORY/lib/glib-2.0/include"
	UI_INCS+=" -I$PWD/dependents/gtk/$GTK_DIRECTORY/lib/gtk-2.0/include"
	UI_LIBS="-L$PWD/dependents/gtk/$GTK_DIRECTORY/lib"
	UI_LIBS+=" -lgtk-win32-2.0 -lgobject-2.0"
	sed "s#@dir@#$GTK_DIRECTORY#g;
		s#@root@#$PREFIX#g;
		s#@lib@#$INST_LIB#g" < dependents/gtk/$MK.in > dependents/gtk/$MK
}

function config_package(){
	sed "s#@package@#$PACKAGE_NAME#g;
		s#@version@#$PACKAGE_VERSION#g;
		s#@arch@#$HOST_ARCH#g;
		s#@depends@#$PACKAGE_DEPENDS#g;
		s#@msi_package@#$PWD/$DIST_PACKAGE#g;
		s#@build_root@#$PWD#g;
		s#@root@#$PREFIX#g;
		s#@bin@#$INST_BIN#g;
		s#@doc@#$INST_DOC#g;
		s#@man1@#$INST_MAN1#g;
		s#@pkg_root@#$PWD$PACKAGE_ROOT_DIR#g;" < toolbox/msi/$MK_IN > toolbox/msi/$MK
	echo "toolbox/msi:$MK_IN ==> $MK"
}
