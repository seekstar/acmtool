#!/bin/bash
i=1
while true; do
	./rand $RANDOM > in.in
	./std < in.in > std.out
	./me < in.in > me.out
	if diff std.out me.out; then
		echo -e -n "\r$i ";
		i=$[$i+1];
	else
		echo WA;
		break;
	fi
done

