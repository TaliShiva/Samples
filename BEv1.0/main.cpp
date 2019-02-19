#include <iostream>
#include <fstream>

#include "../basic_element/include/disk_performer/DiskPerformer.hpp"
//#include "../basic_element/include/data_entity/RawDataWrite.hpp"
//#include "../basic_element/include/data_entity/system/DataAtom.hpp"
//#include "../basic_element/include/data_entity/system/SolidData.hpp"
#include "../basic_element/include/data_entity/system/SolidDataChain.hpp"


#include "../../fio/fio/fio.h"


void open_and_write_in_file(std::string name) {
    std::ofstream my_fd;
    my_fd.open("/home/user/logi/new_log.txt", std::ios_base::app);
    my_fd << name << std::endl;
    my_fd.flush();
    my_fd.close();
}

struct be_data_element {
    io_u *io_us;
    std::shared_ptr<SolidDataChain> chain_;
};

struct be_data {
    unsigned int queued = 0;
    unsigned int commited = 0;
    std::deque<std::shared_ptr<be_data_element>> buffer_;
    std::shared_ptr<DiskPerformer> PDiskPerformer;

};

static struct io_u *fio_be_event(struct thread_data *td, int event) {
    struct be_data *bd = (struct be_data *) td->io_ops_data;
//    std::cout<<"вызывается be_event"<<std::endl;
    return bd->buffer_[event]->io_us;
}

static int fio_be_getevents(struct thread_data *td, unsigned int min_events, unsigned int max_events,
                            const struct timespec *t) {
    struct be_data *bd = (struct be_data *) td->io_ops_data;

    int completed = 0;
    std::cout << "получили события, min_events "<< min_events <<" max_event "<< max_events << std::endl;
//    std::cout << td->files_size << " наименьший и наибольший размер файла " << td->o.file_size_low << "  "
//              << td->o.file_size_high << " имя файла" << td->o.filename << "thread" << td->thread << std::endl;
    if (t != NULL) {
        std::cout << "t " << t << " &t " << &t << std::endl;
        try {
//        unsigned long long timeout = (t->tv_sec * 1000000) + (t->tv_nsec / 1000);
            std::cout << t->tv_sec << "  " << t->tv_sec << "\n";
            std::cout << t->tv_nsec << "  " << t->tv_nsec << "\n";
        }
        catch (std::exception &exception) {

            std::cout << exception.what();

        }
    } else {
        std::cout << "Время незаполнено" << std::endl;
    while (1) {

            if (completed<min_events) {
                usleep(500);
//    for (__useconds_t i = 0; i <= timeout; i += sleep_step) {


                for (auto cock : bd->buffer_) {

                    //std::cout<<"sec "<<t->tv_sec<<" nano_sec "<< t->tv_nsec<< std::endl;
                    std::cout << cock->chain_->getResultCode() << std::endl;
                    if (cock->chain_->isChainCompleted()) {
                        completed++;
                        bd->commited--;
                        std::cout << "Chain completed" << std::endl;
                    } else std::cout << "Chain is not completed" << std::endl;
                }

                std::cout<<"completed" <<completed<<std::endl;
//        if (completed > 0)
//            break;
//        usleep(sleep_step);
//    }
            }
            else return completed;
        }
//        return completed;
    }

}

static int fio_be_commit(struct thread_data *td) {
    struct be_data *bd = (struct be_data *) td->io_ops_data;

    if (!bd->PDiskPerformer)
        return 0;

    for (auto cock : bd->buffer_) {
        try {
            bd->PDiskPerformer->pushSolidDataChain(cock->chain_);
        }
        catch(...){
            open_and_write_in_file("ошибка с пушем Chain-a");
        }
    }
    std::cout<<"сделали commit"<<std::endl;
    bd->commited = bd->queued;
    bd->queued = 0;

    return 0;
}


static int fio_be_queue(struct thread_data *td, struct io_u *io_u) {

    struct be_data *bd = (struct be_data *) td->io_ops_data;

    fio_ro_check(td, io_u);

    if (bd->commited)
        return FIO_Q_BUSY;
    if (io_u->ddir == DDIR_WRITE) {
        try {
            payload_data_vector raw_data(io_u->buflen); // выделяем память для вектора
            memcpy((void *) &raw_data[0], io_u->xfer_buf, io_u->buflen); // сырые данные пихаем в буффер

            auto p_rdw = std::make_shared<RawDataWrite>(raw_data);

            PhysicalRegion pr(0, 0, io_u->offset, io_u->xfer_buflen);

            auto p_da = std::make_shared<DataAtom>(0, pr, p_rdw);
            std::vector<std::shared_ptr<DataAtom>> vec_atoms{p_da};

            auto p_sd = std::make_shared<SolidData>(std::move(vec_atoms));
            std::vector<std::shared_ptr<SolidData>> vec_solid_data{p_sd};

            auto p_sdc = std::make_shared<SolidDataChain>(std::move(vec_solid_data));
            be_data_element bde{io_u, p_sdc};
            auto p_bde = std::make_shared<be_data_element>(bde);
            bd->buffer_.push_back(std::move(p_bde));
        }
        catch (...) {
            std::cerr<<"Обосрались с Queue"<<std::endl;
        }
        bd->queued++;

        return FIO_Q_QUEUED;
    } else {
        std::cerr<<"Флаге не на запись"<<std::endl;
        return FIO_Q_BUSY;
    }
}

static void fio_be_cleanup(struct thread_data fio_unused *td) {
    struct be_data *bd = (struct be_data *) td->io_ops_data;
    if (bd) {
        delete bd;
    }
    std::cout<<"удалили структуру"<<std::endl;
}

static int fio_be_open(struct thread_data fio_unused *td, struct fio_file fio_unused *f) {
    return 0;
}

static int fio_be_init(struct thread_data *td) {
    // struct be_data *bd = (struct be_data *) malloc(sizeof(*bd));
    // memset(bd,0,sizeof(*bd));
    struct be_data *bd = new be_data;
    try {
        auto p_ldq = std::unique_ptr<LocalDiskQueue>(new LocalDiskQueue(std::make_shared<EntityStatisticsBuffer>(0), 1,
                                                                        10)); //ебанутое создание указателя на LocalDiskQueue

        auto p_hwqb = std::unique_ptr<HWQueueMirrorBuffer>(new HWQueueMirrorBuffer());


        auto p_esb = std::unique_ptr<EntityStatisticsBuffer>(new EntityStatisticsBuffer(0));
        auto p_dp = std::unique_ptr<DiskPort>(new DiskPort(td->o.filename));
        //DiskPerformer disk(0,td->o.iodepth,std::move(p_ldq),std::move(p_hwqb),std::move(p_esb),std::move(p_dp)); // создание DiskPerformer-a

        auto p_disk = std::make_shared<DiskPerformer>(0, td->o.iodepth, std::move(p_ldq), std::move(p_hwqb),
                                                      std::move(p_esb), std::move(p_dp));

        bd->PDiskPerformer = p_disk;
        p_disk->startSensorsProcessingThread();
        p_disk->startReceiveResponseThread();
        p_disk->startSendRequestThread();

    }
    catch (std::exception &a) {
        std::cerr << a.what() << std::endl;
        std::cerr << "обосрались с созданием указателей";
    }
    /*if (td->o.iodepth != 1){
        be_data_element *bde = new be_data_element;
        bde->io_us = new io_u [td->o.iodepth];//идея в том, что мы хотим ЗАРАНЕЕ выделить память под дек
    } else
        td->io_ops->flags |= FIO_SYNCIO;*/

    td->io_ops_data = bd;

    return 0;
}
int fio_get_file_size(struct thread_data *td, struct fio_file *ff) {
    ff->real_file_size=10000000;
    fio_file_set_size_known(ff);
    return 0;
}


#ifndef __cplusplus

static struct ioengine_ops ioengine = {
.name		= "BE",
.version	= FIO_IOOPS_VERSION,
.queue		= fio_be_queue,
.commit		= fio_be_commit,
.getevents	= fio_be_getevents,
.event		= fio_be_event,
.init		= fio_be_init,
.cleanup	= fio_be_cleanup,
.open_file	= generic_open_file,
.get_file_size		= fio_get_file_size,
.flags		= FIO_DISKLESSIO | FIO_FAKEIO,
};


static void fio_init fio_be_register(void)
{
register_ioengine(&ioengine);
}

static void fio_exit fio_be_unregister(void)
{
unregister_ioengine(&ioengine);
}

#else

#ifdef FIO_EXTERNAL_ENGINE
extern "C" {
static struct ioengine_ops ioengine;
void get_ioengine(struct ioengine_ops **ioengine_ptr) {// функция возвращает через свой параметр указатель на структуру
    *ioengine_ptr = &ioengine;
    ioengine.name = "BE";
    ioengine.version = FIO_IOOPS_VERSION;
    ioengine.init = fio_be_init;
    ioengine.queue = fio_be_queue;
    ioengine.commit = fio_be_commit;
    ioengine.getevents = fio_be_getevents;
    ioengine.event = fio_be_event;
    ioengine.cleanup = fio_be_cleanup;
    ioengine.open_file = fio_be_open;
    ioengine.get_file_size = fio_get_file_size;
    ioengine.flags = FIO_DISKLESSIO | FIO_FAKEIO;
} ;
}
#endif /* FIO_EXTERNAL_ENGINE */

#endif /* __cplusplus */
