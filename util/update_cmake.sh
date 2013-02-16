#!/bin/sh

set -e -u

update_cmake \
	src/CMakeLists.txt \
	ALDA_FILES \
	include \
	src
