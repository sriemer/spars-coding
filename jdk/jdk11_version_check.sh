#!/bin/bash

# Oracle JDK-11 version update check based on "rpm" and "wget".
# Written for openSUSE Leap.
# Run: ./jdk11_version_check.sh

URI="https://www.oracle.com/technetwork/java/javase/downloads/jdk11-downloads-5066655.html"

VREGEX="jdk-11\.[0-9]\+\.[0-9]\+"

CURRENT=`rpm -qa | grep -o "^$VREGEX" | head -n1`
if [ -z "$CURRENT" ]; then
  echo "ERROR: Cannot determine current JDK-11 version!" >&2
  exit 1
fi

VERSION=`wget -O- ${URI} 2>/dev/null | grep -o "$VREGEX" | head -n1`
if [ -z "$VERSION" ]; then
  echo "ERROR: Cannot determine latest JDK-11 version!" >&2
  exit 2
fi

if [ "$VERSION" != "$CURRENT" ]; then
  echo "An update is available from $CURRENT to $VERSION."
  echo "Update URI: $URI"
else
  echo "Version $VERSION is up-to-date."
fi
