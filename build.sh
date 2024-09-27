#!/usr/bin/env bash

if [ "$#" -eq 1 ]; then
	cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE:STRING="$1" -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
    	  -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++ \
	      -S. -Bbuild -G "Unix Makefiles"
	cmake --build build --config "$1" --target all -j 10 --
else
	printf "script requires 1 argument, received %s.\n" "$#"
fi
