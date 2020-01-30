#!/bin/bash

# Oracle JDK-8 version update check based on "rpm" and "wget".
# Written for openSUSE Leap.
# Run: ./jdk8_version_check.sh

URI="https://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html"

VREGEX="jdk1\.8\-[0-9]\+\.[0-9]\+.[0-9]\+_[0-9]\+"
VREGEX2="jdk-8u[0-9]\+"

CURRENT=`rpm -qa | grep -o "^$VREGEX" | head -n1`
if [ -z "$CURRENT" ]; then
  echo "ERROR: Cannot determine current JDK-8 version!" >&2
  exit 1
fi

VERSION=`wget -O- ${URI} 2>/dev/null | grep -o "$VREGEX2" | head -n1`
if [ -z "$VERSION" ]; then
  echo "ERROR: Cannot determine latest JDK-8 version!" >&2
  exit 2
fi

PATCHL1=`grep -o "[0-9]\+$" <<< "$CURRENT"`
PATCHL2=`grep -o "[0-9]\+$" <<< "$VERSION"`

#echo $PATCHL1
#echo $PATCHL2

if [ "$PATCHL1" != "$PATCHL2" ]; then
  echo "An update is available from $CURRENT to $VERSION."
  echo "Update URI: $URI"
else
  echo "Version $VERSION is up-to-date."
fi
