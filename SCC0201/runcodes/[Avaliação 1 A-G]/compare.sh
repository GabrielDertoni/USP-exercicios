#!/usr/bin/env bash

mkdir outs

seq 10 | parallel "echo {} | ./modificado > {}.out"
seq 10 30 | parallel "echo {} | ./modificado > {}.out"
seq 50 100 | parallel "echo {} | ./modificado > {}.out"

seq 10 | parallel "echo {} | ./original > {}.out"
seq 10 30 | parallel "echo {} | ./original > {}.out"
seq 50 100 | parallel "echo {} | ./original > {}.out"

find ./outs/*.in | parallel "diff --color=always -u --label GOT --label EXPECTED {.}.out {}"

rm outs/*
rmdir outs