#!/bin/bash

# Zoom version update check based on "rpm" and "wget".
# Written for openSUSE Leap.
# Run: ./zoom_version_check.sh

URI="https://zoom.us/download"

VREGEX="[0-9]\+\.[0-9]\+\.[0-9]\+"

CURRENT=`rpm -q zoom | grep -o "$VREGEX"`
if [ -z "$CURRENT" ]; then
  echo "ERROR: Cannot determine current Zoom version!" >&2
  exit 1
fi

VERSION=`wget -O- ${URI} 2>/dev/null | grep "ver-text.*Version" | \
  grep -o "$VREGEX"`
if [ -z "$VERSION" ]; then
  echo "ERROR: Cannot determine latest Zoom version!" >&2
  exit 2
fi

if [ "$VERSION" != "$CURRENT" ]; then
  echo "An update is available from $CURRENT to $VERSION."
  echo "Update URI: $URI"
else
  echo "Version $VERSION is up-to-date."
fi
