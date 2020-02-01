#!/usr/bin/env bash

LIBS=(--library alda --library fcppt)
DIRS=(examples include src tests)

prettify_includes "${LIBS[@]}" "${DIRS[@]}"
