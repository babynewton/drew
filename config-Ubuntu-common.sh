#!/bin/bash

PACKAGE_EXTENSION=deb
PACKAGE_FORMAT=debian
PACKAGE_DEPENDS="libc6(>=2.15)"

INST_BIN=/bin
INST_DOC=/share/doc/$PACKAGE_NAME
INST_MAN1=/share/man/man1
INST_EXAMPLE=/share/$PACKAGE_NAME

function config_package(){
	test -n "which help2man" || sudo apt-get install help2man
	test $VERBOSE == false || echo Dependents:$PACKAGE_DEPENDS
	sed "s#@package@#$PACKAGE_NAME#g;
		s#@version@#$PACKAGE_VERSION#g;
		s#@arch@#$HOST_ARCH#g;
		s#@depends@#$PACKAGE_DEPENDS#g;
		s#@debian_package@#$PWD/$DEBIAN_PACKAGE#g;
		s#@build_root@#$PWD#g;
		s#@root@#$PREFIX#g;
		s#@bin@#$INST_BIN#g;
		s#@doc@#$INST_DOC#g;
		s#@man1@#$INST_MAN1#g;
		s#@pkg_root@#$PWD$PACKAGE_ROOT_DIR#g;" < toolbox/debian/$MK_IN > toolbox/debian/$MK
	echo "toolbox/debian:$MK_IN ==> $MK"
}


