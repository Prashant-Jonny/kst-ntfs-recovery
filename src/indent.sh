#/bin/bash

for i  in ./*.cpp; do indent -gnu $i ; done
for i  in ./*.h; do indent -gnu $i ; done
