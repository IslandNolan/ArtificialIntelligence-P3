#!/bin/bash

cd src/sources &&
glib-compile-resources intelliapp.gresource.xml --target=resources.c --generate-source &&
ls -l &&
cd ../..
