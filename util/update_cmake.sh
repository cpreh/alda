#!/usr/bin/env bash

set -e -u

update_cmake \
	CMakeLists.txt \
	ALDA_FILES \
	include \
	src

update_cmake \
	net/CMakeLists.txt \
	ALDA_NET_FILES \
	net
