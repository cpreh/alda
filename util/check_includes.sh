#!/bin/bash

INCLUDE_BINARY="check_includes"

"${INCLUDE_BINARY}" include || exit

"${INCLUDE_BINARY}" net/include || exit

"${INCLUDE_BINARY}" net/impl/include || exit
