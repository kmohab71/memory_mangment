#!/bin/bash
make
files=$(ls input*.txt);
for filename in $files; do
	output=${filename/input/output};
	echo 'Testing' $filename 'and comparing with' $output;
	echo $(cat $filename | ./lab4 | diff $output -)
done