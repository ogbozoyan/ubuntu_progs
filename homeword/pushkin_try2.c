#include <stdio.h>
#include <string.h>
#include "poema.h"

#define _GNU_SOURCE //for work asprintf

char* pushkin(char* text){
	
	int lines = 0;
	lines = 152;						
	int adres = 0;
	int i = 0;
	if (text == NULL) 
	{
		return poema[0];
	} 
	else 
	{	
		for (i ;i < lines;i++)		
			if (strstr(text, poema[i]))
				adres++;//index with we should to print
		asprintf(&text, "%s%s%c", text, poema[adres],'\n');
		
		return text;
	}
}	