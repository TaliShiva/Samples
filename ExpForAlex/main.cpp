#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void* start_thread(void* message){
    int unused;
    int ret;

    ret = pthread_setcanceltype(PTHREAD_CANCEL_DISABLE,&unused);
    if(ret){
        errno = ret;
        perror("pthread_setcanceltype");
        return 0;
    }
    ret = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,&unused);
    if(ret){
        errno = ret;
        perror("pthread_setcancelstate");
        return 0;
    }

    while(1) {
        printf("%s\n", (const char *) message);
    }
    return message;
}

int main(void) {
    pthread_t my_cock1, my_cock2;
    const char *message1 = "I have big dick";
    const char *message2 = "But I have small ass";

//установили разрешение на свою отмену и установили её как отложенную

    pthread_create(&my_cock1,NULL,start_thread,(void*)message1);
    pthread_create(&my_cock2,NULL,start_thread,(void*)message2);
    sleep(3);
int ret;
    ret = pthread_cancel(my_cock1);

    if(ret){
        errno = ret;
        perror("pthread_cancel");
        return -1;
    }
    pthread_join(my_cock2,NULL);

    return 0;
}