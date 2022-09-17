#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
//-pthread
int a[10][10],b[10][10],c[10][10];
int size,i,j,k;

void firstfile(char **argv);
void secondfile(char **argv);
void result(char **argv);
void mul(char **argv);
void work(char **argv);


int main(int argc,char** argv,char** env){
    if(argc < 3){
        printf("usage: %s mat1.txt mat2.txt res.txt\n",argv[0]);
        return 0;
    }
    pthread_t thread_work;
    pthread_create(&thread_work,NULL,work,argv);
    //mul(argv);
    pthread_join(thread_work,NULL);
return 0;
}

void firstfile(char **argv){
    FILE *f1;
    f1 = fopen(argv[1], "r");
    
    fscanf(f1, "%d", &size);
    
    for (i = 0; i < size; ++i){
        for (j = 0; j < size; ++j){
                fscanf(f1, "%d", &a[i][j]);
            }
        }
        fclose(f1);
    
}
void secondfile(char **argv){
    FILE *f2;
    f2 = fopen(argv[2], "r");

    for (i = 0; i < size; ++i){
        for (j = 0; j < size; ++j){
                fscanf(f2, "%d", &b[i][j]);
                }
            }
    fclose(f2);

}
void result(char **argv){
    FILE *res;
    res = fopen(argv[3], "w+");
 
    for ( i = 0; i < size; ++i ){
            for ( j = 0; j < size; ++j ){
        fprintf(res, "%5d", c[i][j]);
        }
    fprintf(res,"%c",'\n');
    }
 
    fclose(res);
}
void mul(char **argv){
   for(i=0; i < size; i++){
            for(j=0; j < size; j++){
                c[i][j]=0;
            for(k=0; k < size; k++)
                c[i][j]+=a[i][k]*b[k][j];
            }
    } 
}
void work(char **argv){
    pthread_t threadf1;
    pthread_t threadf2;
    pthread_t threadres;
    pthread_t thread_mul;

    pthread_create(&threadf1,NULL,firstfile,argv);
    pthread_join(threadf1, NULL);
    pthread_create(&threadf2,NULL,secondfile,argv);
    pthread_join(threadf2, NULL);
    pthread_create(&thread_mul,NULL,mul,argv);
    pthread_join(thread_mul,NULL);   
    pthread_create(&threadres,NULL,result,argv);
    pthread_join(threadres, NULL);
    
    printf("Done.\n");
    
}
