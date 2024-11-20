#!/bin/bash

app_binary="EpiKodi"

clean_app() {
    rm -f $app_binary
    rm -f libs/*
}

clean_tests() {
    rm -f $tests_binary
}

clean_all() {
    clean_app
    clean_tests
}

compile_tests () {
    clean_all
    cmake -S . -B build -DTESTS=ON -DBUILD=ON
    cd build
    make
    cd ..
    # ./build/tests/$tests_binary
}

compile() {
    clean_all
    mkdir components
    cmake -S . -B build -DTESTS=OFF -DBUILD=ON
    cd build
    make
    cd ..
}

rm -rf build
if [ "$1" == "clean" ]; then
    clean_all
elif [ "$1" == "tests" ]; then
    compile_tests
else
    compile
fi