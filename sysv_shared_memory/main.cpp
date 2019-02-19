#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <cstdio>
//sysV-шный стиль
int main(void) {

    pid_t pid;
    char *shared; // указатель на область общей памяти
    int shmid;

    shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (fork() == 0) { /* Ребёнок */
        /* Добавляем в общую память и выводим что получилось*/
        shared = (char*)shmat(shmid, (void *) 0, 0);
        printf("Child pointer  %p\n", shared);
        *shared='a';
        printf("Child value=%c\n", *shared);
        sleep(3);
        printf("Child value=%c\n", *shared);

    } else { /* Родитель */
        /* Добавляем в общую память и выводим что получилось*/
        shared = (char*)shmat(shmid, (void *) 0, 0);
        sleep(1);
        printf("Parent pointer %p\n", shared);
        printf("Parent value=%c\n", *shared);
        sleep(1);
        *shared='b';
        printf("Parent value=%c\n", *shared);
        sleep(5);
        shmctl(shmid, IPC_RMID, 0);
    }
}