#!/bin/bash
# snippet come from https://superuser.com/a/1288646/1542419
if [ "$0" = "$BASH_SOURCE" ]; then
	echo "Error: Script must be sourced"
	exit 1
else
	echo -n "Setting xuxiake environment ... "
fi
export CROSS_COMPILE=aarch64-none-linux-gnu-
export PATH=$PATH:$PWD/../buildroot/output/host/bin/
echo "ok"
