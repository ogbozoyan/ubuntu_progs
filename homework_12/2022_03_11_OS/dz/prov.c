
#include <pthread.h>
 
//потоковая функция
void* threadFunc(void* thread_data){
	//завершаем поток
	pthread_exit(0);
}
 
int main(){
 
	//какие то данные для потока (для примера)
	void* thread_data = NULL;
 
	//создаем идентификатор потока
	pthread_t thread;
 
	//создаем поток по идентификатору thread и функции потока threadFunc
	//и передаем потоку указатель на данные thread_data
	pthread_create(&thread, NULL, threadFunc, thread_data);
	
	//ждем завершения потока
	pthread_join(thread, NULL);
 
	return 0;
}