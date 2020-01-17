#!/usr/bin/env bash

ARGS=(--library alda --library fcppt)

find examples include src tests \( \( -name '*.hpp' -o -name '*.cpp' \) \) -exec update_headers.sh '{}' "${ARGS[@]}" \;
