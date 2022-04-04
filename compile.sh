#/bin/bash

cd src/sources
glib-compile-resources --target=resources.c --generate-source intelliapp.gresource.xml
cd ../..
cmake --build cmake-build-debug/
./cmake-build-debug/Project3

