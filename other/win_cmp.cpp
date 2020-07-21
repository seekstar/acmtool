#include <cstdio> 
#include <cstdlib>

using namespace std;

int main()
{
	int i;
	int errorlevel;
	system("@echo off");
	for(i = 1; ; ++i)
	{
		printf("%d:", i);
		system("rand.exe %random%>in.in");
		system("std.exe<in.in>std.out");
		system("me.exe<in.in>me.out");
		errorlevel = system("fc std.out me.out");
		if(errorlevel == 1)system("pause");
	}
	
	return 0;
}

