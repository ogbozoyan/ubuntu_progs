#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

FILE* f;
void __attribute__((constructor)) constructor(void){


	char buf[256] = "";
	f = fopen("log.txt","w+");

	int i = 0;
	int j = 0;
	int f1 = open("proc/cmdline","r");

	

	if(f1 ==  -1){
		printf("Can't open /proc/self/cmdline \n");
		exit(1);
	}
	//reading char by char from /proc/self/cmdline
	while(read(f1 ,buf, sizeof(buf)) > 0){
			printf("%s \n",buf);			
	}
}
void __attribute__((destructor)) destructor(void){

	fclose(f);
}