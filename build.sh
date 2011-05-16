#!/bin/sh
CFLAGS="$CFLAGS `pkg-config --cflags glib-2.0`"
LIBFLAGS="$CFLAGS `pkg-config --libs glib-2.0`"

gcc -Wall -Werror $LIBFLAGS $CFLAGS src/*.c -o araneidae
