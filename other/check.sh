#!/bin/bash
i=1
while true; do
	./rand.exe $RANDOM > input.txt
	./me.exe < input.txt > me.txt
	./std.exe < input.txt > std.txt
	if ./check.exe; then
		echo -e -n "\r$i ";
		i=$[$i+1];
	else
		echo WA;
		break;
	fi
done

