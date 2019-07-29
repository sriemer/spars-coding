#!/bin/sh

CWD="`dirname $0`"
cd "${CWD}"

export LD_LIBRARY_PATH="lib1:lib2"

./statmemlib
