#!/usr/bin/env bash

cmake -Bbuild -H. && cd build && make && cd ../ && ./fractal-playground
