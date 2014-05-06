#!/bin/bash

PACKAGE_DEPENDS="libgtk2.0-0"
PACKAGE_EXTENSION=deb
PACKAGE_FORMAT=debian

PACKAGE_DEPENDS_LUA=liblua5.1-0
PACKAGE_DEPENDS_LUAJIT=libluajit-5.1-2

INST_BIN=/bin
INST_DOC=/share/doc/$PACKAGE_NAME
INST_MAN1=/share/man/man1
INST_EXAMPLE=/share/$PACKAGE_NAME

function config_tools(){
	DEVS="liblua5.1-0-dev libluajit-5.1-dev libgtk2.0-dev help2man"
	for DEV in $DEVS
	do
		echo installing $DEV
		sudo apt-get install $DEV
	done
}

function config_package(){
	sed "s#@package@#$PACKAGE_NAME#g;
		s#@version@#$PACKAGE_VERSION#g;
		s#@arch@#$HOST_ARCH#g;
		s#@depends@#$PACKAGE_DEPENDS#g;" < toolbox/debian/control.in > toolbox/debian/control
	sed "s#@package@#$PACKAGE_NAME#g;
		s#@debian_package@#$PWD/$DEBIAN_PACKAGE#g;
		s#@build_root@#$PWD#g;
		s#@root@#$PREFIX#g;
		s#@bin@#$INST_BIN#g;
		s#@doc@#$INST_DOC#g;
		s#@man1@#$INST_MAN1#g;
		s#@pkg_root@#$PWD$PACKAGE_ROOT_DIR#g;" < toolbox/debian/$MK_IN > toolbox/debian/$MK
	echo "toolbox/debian:$MK_IN ==> $MK"
}


