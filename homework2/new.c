#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <mcheck.h>
#include <string.h>

//algoritm MALLOC_TRACE=mem.log ./a.out
//mtrace ./a.out mem.log

void* res[1000] = {NULL}; //for keeping malloc result
int i = 0;
int flag = 0;

void __attribute__((constructor)) con(){
	NULL;
}

void* new(size_t x){  
	i++;
	
	if (i >= 1000){
		flag = 1;
		fprintf(stdout, "Error");
		i = 0;
	}
	
	res[i] = malloc(x);
	
	if(res[i] == NULL){
		fprintf(stdout,"Put argument");

	}

	return (res);
}

void __attribute__((destructor)) free_new(){
	
	if(flag){
	
	for(int j = 0;j<1000;j++){
	free(res[j]);
	
	}

}
	
	else{
		
		for(int j = 0;j<i;j++){
			
			free(res[j])
		}
	}
}

int main(){
	mtrace();
	int i = new(20);
	return 0;
}
