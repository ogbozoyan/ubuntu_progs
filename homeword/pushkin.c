#include <stdio.h>

 char array[5][256] = {
        {"a\n"},
        {"b\n"},
        {"c\n"},
        {"d\n"},
        {"e\n"}
};

char* pushkin(char* text){
        
        int len = sizeof(text);
        char *buf = NULL;
        //for (int i = 0;)
        
        if (text == NULL){
                text = &(array[0][256]);
                return (text);
        } 
        else if (text != NULL){
                
                buf = (array[0][256]);
                
                text = buf;
                return (text);
        }

}

int main (){
        char arr[] = {'a','b'};

        printf("%s",pushkin(NULL));

        return 0;
}