#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/fs.h>

#include <unistd.h>

//get_block - для файла связанноо с заданным fd, возвращает физический блок, ассоциированный с logical_block

int get_block(int fd, int logical_block){
    int ret;
    ret = ioctl(fd, FIBMAP, &logical_block);//нужно для соответствующего типа устройства сделать
    if(ret<0){
        perror("ioctl");
        return -1;
    }
    return logical_block;
}

//get_nr_blocks возвращает количество логических блоков, занимаемых файлом связанным с fd
int get_nr_blocks(int fd){
    struct stat buf;
    int ret;

    ret = fstat(fd,&buf);
    if(ret < 0){
        perror("fstat");
        return -1;
    }
    return buf.st_blocks;
}
//print_blocks - для каждого логического блока, занимаемого файлом, ассоциированным с fd
//выдает в стандартный вывод пару значений - (логич блок - физич блок)
void print_blocks(int fd){
    int nr_blocks, i;
    nr_blocks = get_nr_blocks(fd);

    if(nr_blocks<0){
        fprintf(stderr, "get_nr_blocks failed!\n");
        return;
    }

    if(nr_blocks==0){
        printf("no allocated blocks\n");
        return;
    } else if (nr_blocks == 1)
        printf("1 blocks\n\n");
    else
        printf("%d blocks \n\n", nr_blocks);

    for (int i = 0; i < nr_blocks;++i) {
        int phys_blocks;
        phys_blocks = get_block(fd,i);
        if(phys_blocks<0){
            fprintf(stderr, "get_blocks failed!\n");
            return;
        }
        if (!phys_blocks)
            continue;
        printf("(%u, %u) ", i, phys_blocks);
    }
    putchar('\n');
}

int main(int argc, char *argv[]) {
    int fd;
    if (argc<2){
        fprintf(stderr,"usage %s <file>\n", argv[0]);
    }

    fd = open(argv[1],O_RDONLY);
    if (fd < 0){
        perror("open");
        return 1;
    }
    print_blocks(fd);

    //Так можно получить PID
    pid_t getpid(void);
    printf("My pid=%jd\n", (intmax_t)getpid());


    return 0;
}