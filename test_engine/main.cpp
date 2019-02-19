//#include <aio.h>

#include <iostream>
#include <fstream>

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "../../fio/fio/fio.h"



void open_and_write_in_file(std::string name,struct thread_data *td) {
    std::ofstream my_fd;
    my_fd.open("/home/user/logi/new_log.txt", std::ios_base::app);
    my_fd << name << std::endl;
    my_fd<< "td->files_size"<< td->files_size <<std::endl;
    my_fd<<"td->done" << td->done <<std::endl;
    my_fd<< "low and hight"<<td->o.file_size_low << td->o.file_size_high <<std::endl;
    my_fd.flush();
    my_fd.close();
}

struct myaio_data {
    struct io_u **io_us;
    unsigned int queued;
    int events;
};

/*Ключ -> event () вызывается для соответствия номеру события с помощью io_u.
 * После того, как ядро вызвало -> getevents (),
 * и оно вернулось, например, 3, hook -> event () должен вернуть 3 события,
 * которые были завершены , -> event () с [0-2].*/
static struct io_u *fio_myaio_event(struct thread_data *td, int event){
   // open_and_write_in_file("fio_myaio_event");
    struct myaio_data *md = (struct myaio_data *)td->io_ops_data;
    return md->io_us[event];
}


/* Ключ -> getevents () используется для получения завершенных событий от асинхронного движка.
 * Он возвращает количество завершенных событий со времени последнего вызова, которое затем можно получить,
 * вызвав hook -> event () с номерами событий.
*/
static int fio_myaio_getevents(struct thread_data *td, unsigned int min_events, unsigned int fio_unused max,
                                const struct timespec fio_unused *t){
    open_and_write_in_file("fio_myaio_getevents",td);


    struct myaio_data *md = (struct myaio_data *)td->io_ops_data;
    int ret = 0;
    if (min_events){
        ret = md->events;
        md->events;
    }

    return ret;
}

//commit не описан в skeleton
// но видимо выкидываем из очереди данные в события event
static int fio_myaio_commit(struct thread_data *td){
   // open_and_write_in_file("fio_myaio_commit");
    struct myaio_data *md = (struct myaio_data*) td->io_ops_data;
    if(!md->events){
        // эта хуета указывается при компиляции
#ifndef FIO_EXTERNAL_ENGINE
        io_u_mark_submit(td, md->queued);
#endif
        md->events = md->queued;
        md->queued = 0;

    }
}

/*Ключ -> queue () отвечает за инициализацию io на передаваемом io_u.
 * Если движок io является синхронным, io может завершить работу до -> queue().
 *
 * Io-движок должен передавать в направлении, указанном в io_u-> ddir, в буфер, на который указывает io_u-> xfer_buf,
 * столько же байтов, сколько io_u-> xfer_buflen. Количество остаточных данных может быть установлено в io_u->resid
 * для короткого чтения / записи.
 * */
static int fio_myaio_queue(struct thread_data *td, struct io_u *io_u){

    struct myaio_data *md = (struct myaio_data *) td->io_ops_data;

   // open_and_write_in_file("fio_myaio_queue");


    fio_ro_check(td, io_u); // Двойная проверка, чтобы поймать ошибочную запись в режиме только для чтения

    if(td->io_ops->flags & FIO_SYNCIO)
        return FIO_Q_COMPLETED;// передаётся в случае завершения запроса
    //рассматривается несинхронный случай
    if(md->events)
        return FIO_Q_BUSY;// если мы не можем находится в очереди на этом этапе

    md->io_us[md->queued++] = io_u;// добавление событий io_u в нашу очередь io_us
   // open_and_write_in_file("ddir: "+std::to_string(io_u->ddir));


    return FIO_Q_QUEUED; //io_u добавлена в очередь
}

//открытие файла, в данном случае условное
static int fio_myaio_open(struct thread_data fio_unused *td,
                         struct fio_file fio_unused *f)
{
  //  open_and_write_in_file("fio_myaio_open");
    return 0;
}

// очистка данных
static void fio_myaio_cleanup(struct thread_data fio_unused *td){
    struct myaio_data *md = (struct myaio_data *) td->io_ops_data;
   // open_and_write_in_file("fio_myaio_cleanup");
    if(md){
        free(md->io_us);
        free(md);
    }

};

// выделяем память под наши структуры данных и присваиваем их td-шке
static int fio_myaio_init(struct thread_data *td){

   // open_and_write_in_file("fio_myaio_init");

    struct myaio_data *md = (struct myaio_data *) malloc(sizeof(*md));//можно заменить на плюсовое выделение памяти
    memset(md,0,sizeof(*md));//заменит инициализацию нулями на плюсовую
    if (td->o.iodepth != 1) {
        md->io_us = (struct io_u **) malloc(td->o.iodepth * sizeof(struct io_u *));//выделяется память под массив указателей io_u
        memset(md->io_us,0,td->o.iodepth*sizeof(struct io_u *));
    } else
        td->io_ops->flags |= FIO_SYNCIO; /* io engine has synchronous ->queue */

    td->io_ops_data = md;

    return 0;
}
#ifndef __cplusplus

static struct ioengine_ops ioengine = {
	.name		= "null",
	.version	= FIO_IOOPS_VERSION,
	.queue		= fio_myaio_queue,
	.commit		= fio_myaio_commit,
	.getevents	= fio_myaio_getevents,
	.event		= fio_myaio_event,
	.init		= fio_myaio_init,
	.cleanup	= fio_myaio_cleanup,
	.open_file	= fio_myaio_open,
	.flags		= FIO_DISKLESSIO | FIO_FAKEIO,
};


static void fio_init fio_myaio_register(void)
{

   // open_and_write_in_file("fio_myaio_register");

    register_ioengine(&ioengine);
}

static void fio_exit fio_myaio_unregister(void)
{
   // open_and_write_in_file("fio_myaio_unregister");
    unregister_ioengine(&ioengine);
}

#else

#ifdef FIO_EXTERNAL_ENGINE
extern "C" {
static struct ioengine_ops ioengine;
void get_ioengine(struct ioengine_ops **ioengine_ptr){// функция возвращает через свой параметр указатель на структуру
    *ioengine_ptr = &ioengine;
    ioengine.name           = "myaio";
    ioengine.version        = FIO_IOOPS_VERSION;
    ioengine.init           = fio_myaio_init;
        //.prep		        = fio_myaio_prep,
    ioengine.queue          = fio_myaio_queue;
    ioengine.commit         = fio_myaio_commit;
        //.cancel		    = fio_myaio_cancel,
    ioengine.getevents      = fio_myaio_getevents;
    ioengine.event          = fio_myaio_event;
    ioengine.cleanup        = fio_myaio_cleanup;
    ioengine.open_file      = fio_myaio_open;
    ioengine.flags          = FIO_DISKLESSIO | FIO_FAKEIO;
    //.close_file	        = generic_close_file,
    //.get_file_size        = generic_get_file_size,
    //options		        = options,
    //.option_struct_size	= sizeof(struct fio_skeleton_options),
};
}
#endif /* FIO_EXTERNAL_ENGINE */

#endif /* __cplusplus */



