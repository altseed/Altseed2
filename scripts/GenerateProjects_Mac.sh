#!/bin/sh

echo set current directory
cd `dirname $0`

mkdir ../build

cd ../build

cmake -D BUILD_TEST=ON ../ -G "Xcode" -T buildsystem=1
