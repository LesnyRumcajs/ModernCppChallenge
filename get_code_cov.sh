#!/bin/bash
for filename in `find src/ | egrep '\.cpp'`;
do
  gcov -n -o . $filename > /dev/null;
done