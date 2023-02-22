#!/bin/bash

cd src/sources
glib-compile-resources --target=resources.c --generate-source intelliapp.gresource.xml
cd ../..
cmake --build build/
cd build/
cp ArtificialIntelligenceP3 ../

echo "Success! Binary is Located at: Full Path here. "

