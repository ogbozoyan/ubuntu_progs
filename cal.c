#include <stdio.h>

int a = 10;
int b = 5;
int cal(int a,int b){
	int c = 0;
	c = a + b;

	return c;
}

int main(){
	int res = 0;
	res = cal(a,b);
	printf("%d",res);
	return 0;
}	
