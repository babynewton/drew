#!/bin/bash

PACKAGE_EXTENSION=exe
PACKAGE_FORMAT=msi

INST_BIN=/
INST_DOC=/
INST_EXAMPLE=/examples

CORES=$NUMBER_OF_PROCESSORS

function init_luajit(){
	SCRIPT_TARGET=luajit
}

function init_lua(){
	SCRIPT_TARGET=lua
}

function init_gtk(){
	UI_TARGET=gtk
}

function config_package(){
	echo TODO: setup package
}
