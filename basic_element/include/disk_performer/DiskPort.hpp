#pragma once

#include <libaio.h>
#include <atomic>

#include "../../include/disk_performer/hw_queue_mirror/HWQueueMirrorElement.hpp"

/**
 * Maximum count iovecs support in kernel in single request(defined in kernel, read  man 2 pwritev)
 */
const unsigned MAX_IOVECS_SIZE = 1024;

class diskPortInterruptWaitException : public std::exception {};
/**
 * Limit of DataAtom in SolidData exceeded
 */
class overflowDataAtomCountInSolidDataException : public std::exception {};


#ifdef __cplusplus
extern "C" {
#endif
// For big endian, 64 bits
#define PADDED(x, y)    x, y
#define PADDEDptr(x, y)    x
#define PADDEDul(x, y)    unsigned long x

/**
 * Common struct for libaio
 * only changed type of member data
 */
struct c_iocb {
    unsigned long long data;    /* Return in the io completion event */
    PADDED(unsigned key, __pad2);    /* For use in identifying io requests */

    short aio_lio_opcode;
    short aio_reqprio;
    int aio_fildes;

    union {
        struct io_iocb_common c;
        struct io_iocb_vector v;
        struct io_iocb_poll poll;
        struct io_iocb_sockaddr saddr;
    } u;
};

/**
 * Common struct for libaio
 * only changed type of member data
 */
struct c_io_event {
    unsigned long long data;
    PADDEDptr(struct c_iocb *obj, __pad2);
    PADDEDul(res, __pad3);
    PADDEDul(res2, __pad4);
};
}

using disk_error_code = long;

class DiskPort {
public:
    explicit DiskPort(const std::string &device_path);

    DiskPort(const DiskPort &) = delete;

    DiskPort &operator=(const DiskPort &) = delete;

    DiskPort(DiskPort &&) = delete;

    DiskPort &operator=(DiskPort &&) = delete;

    /**
     * @brief Put write operation with SolidData to kernel queue
     * @param solid_data_ptr pointer to SolidData
     * @param callback_id unique id
     * @throw overflowDataAtomCountInSolidDataException, std::system_error
     */
    void asyncWrite(const std::shared_ptr<SolidData> solid_data_ptr,
                    callback_id_type callback_id);

    /**
     * @brief Receiving a response about the completion of the processing operation.
     * If there are no completed operations, the call is blocked until any operation is completed.
     * If the shutdown() is called, the wait is interrupted with the exception diskPortInterruptWaitException.
     * @param is_last_answer set to true if kernel queue contain only one operation
     * @return callback_id - unique id, disk_error_code - operation exit code
     * @throw diskPortInterruptWaitException, std::system_error
     */
    std::pair<callback_id_type, disk_error_code> waitAndGetAnswer(bool is_last_answer);

    /**
     * @brief Graceful stop working (correct interruption endless loop)
     */
    void shutdown();

    ~DiskPort();


private:
    std::string device_path_;
    io_context_t ioctx_;
    int fd_;
    /**
     * @brief maximum kernel aio queue size
     */
    unsigned kernel_queue_max_events_;
    /**
     * @brief timeout for statistics calculation
     */
    timespec get_events_timeout_;
    std::atomic_bool stop_working_;

};



