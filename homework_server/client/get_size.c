#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // для int64_t
#include <inttypes.h> // для правильного вывода int64_t в printf
 
int64_t getFileSize(const char* file_name){
    int64_t _file_size = 0;
    FILE* fd = fopen(file_name, "rb");
    if(fd == NULL){
        _file_size = -1;
    }
    else{
        while(getc(fd) != EOF)
            _file_size++;
        fclose(fd);
    }
    return _file_size;
}
 
#define FILE_PATH "some_file.txt"
 
int main(){
    int64_t file_size = getFileSize("file.txt");
    printf("File size: %" PRId64 "\n", file_size);
 
    return 0;
}