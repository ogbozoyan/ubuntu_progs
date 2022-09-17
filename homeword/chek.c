#include <stdio.h>
#include <stdlib.h>

int main(){
	int *k;
	k = (int*)malloc(sizeof(int)); 
	int i = 0;
	
	char array[5][k] =   {
		{"stroka 1 \n"},
		{"stroka 2 \n"},
		{"stroka 3 \n"},
		{"sroka 4 \n"},
		{"stroka 5 \n"}
	};
	

	
	while(i < k){
		printf("%c",array[0][i]);
		i++;

	}
	//din array
	//char din = 
	return 0;

}