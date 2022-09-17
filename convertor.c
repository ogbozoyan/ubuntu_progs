#include <stdio.h>
#include <string.h>

char* flip(char* mas){
	char buf;
	for(int i=0;i < strlen(mas);i++){
		if(mas[i] == '.'){
			mas[i] = 'p';
		}
	}
	return mas;
}

int main(){
	
	char string[20];

	strcpy(string,"...l..\n");

	printf("%s", flip(string));	

	return 0;
}
	
