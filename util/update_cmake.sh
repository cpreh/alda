#!/usr/bin/env bash

set -e -u

update_cmake.sh \
	files.txt \
	include \
	src

update_cmake.sh \
	net/files.txt \
	net
