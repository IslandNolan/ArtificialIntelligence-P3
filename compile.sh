#!/bin/bash

cd src/sources
glib-compile-resources --target=resources.c --generate-source intelliapp.gresource.xml
cd ../..
cmake --build build/
cd build/
cp ArtificialIntelligenceP3 ../
cd ..

echo "Success! Binary is Located at: $(pwd)/ArtificialIntelligenceP3"

