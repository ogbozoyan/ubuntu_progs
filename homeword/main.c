#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char *argv[])
{
    void *handle;
    char* text = NULL;

    handle = dlopen("./puskin.so", RTLD_LAZY);
    if ( NULL == (handle) ) {
	fprintf(stderr, "Ошибка загрузки библиотеки: %s\n", dlerror());
	return -1;
    }
 
    char* (*pushkin)(char*); 
    pushkin = dlsym(handle, "pushkin");

    if ( NULL != pushkin ) {
	text = pushkin(text);
	puts(text);
    } 
    else {
	fprintf(stderr, "Ошибка получения функции: %s\n", dlerror());
    }
    
    dlclose(handle);
    return  ( NULL == pushkin ) ? (-1) : (0);
}