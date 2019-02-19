
#define BOOST_LOG_DYN_LINK

#include <cstring>
#include <system_error>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <boost/log/trivial.hpp>

#include "../../include/disk_performer/DiskPort.hpp"



DiskPort::DiskPort(const std::string &device_path) : device_path_(device_path),
                                                     ioctx_(nullptr),
                                                     fd_(0),
                                                     kernel_queue_max_events_(100)
{
    get_events_timeout_ = {0, 100000000}; // Set timeout for 1 seconds
    stop_working_.store(false);
    fd_ = open(device_path_.c_str(), O_RDWR | O_DIRECT);
    if (fd_ <= 0) {
        throw std::system_error(errno, std::system_category(), "Error openning device: " + device_path_);
    } else {
        BOOST_LOG_TRIVIAL(trace) << "Device " << device_path_ << " was successfully opened";
    }
    int res = io_setup(kernel_queue_max_events_, &ioctx_);
    if (res != 0) {
        BOOST_LOG_TRIVIAL(trace) << "Error io_setup: "
                                 << std::error_condition(-res, std::generic_category()).message();
        throw std::system_error(-res, std::system_category(),
                                "Error getting io_setup: " + std::to_string(-res) + " : ");
    }
}

DiskPort::~DiskPort() {
    BOOST_LOG_TRIVIAL(trace) << "Destructor DiskPort begin";
    int res = io_destroy(ioctx_);
    if (res != 0) {
        BOOST_LOG_TRIVIAL(warning) << "Error io_destroy: "
                                   << std::error_condition(-res, std::generic_category()).message();
    }
    if (fd_ != 0) {
        close(fd_);
    }
    BOOST_LOG_TRIVIAL(trace) << "Destructor DiskPort ended";
}

void DiskPort::asyncWrite(const std::shared_ptr<SolidData> solid_data_ptr, callback_id_type callback_id) {
    if(solid_data_ptr->data_atoms.size() > MAX_IOVECS_SIZE) {
        /* Vector of iovecs can be no longer than 1024, it's kernel limitaion
         * more information can read from man 2 pwritev
         */
        throw overflowDataAtomCountInSolidDataException();
    }
    struct c_iocb iocb = {};
    struct c_iocb *iocbs = &iocb;
    std::vector<iovec> data_atom_iovecs(solid_data_ptr->data_atoms.size());
    std::transform(solid_data_ptr->data_atoms.begin(), solid_data_ptr->data_atoms.end(), data_atom_iovecs.begin(),
                   [](const std::shared_ptr<DataAtom> &atom) -> iovec {
                       return iovec{&atom->raw_data_write_ptr->data.at(atom->raw_data_offset),
                                    atom->physical_region.disk_length};
                   });
    io_prep_pwritev(reinterpret_cast<::iocb *>(&iocb), fd_, &data_atom_iovecs.at(0), data_atom_iovecs.size(),
                    solid_data_ptr->data_atoms.at(0)->physical_region.disk_offset);
    iocb.data = callback_id;
    int res = io_submit(ioctx_, data_atom_iovecs.size(), reinterpret_cast<::iocb **>(&iocbs));
    if (res >= 0) {
        BOOST_LOG_TRIVIAL(trace) << "DiskPort::asyncWrite Send id: " << callback_id;
    } else {
        BOOST_LOG_TRIVIAL(trace) << "DiskPort::asyncWrite Error id: " << callback_id << ", code: " << res;
        throw std::system_error(-res, std::system_category(), "Error submit aio pwritev request");
    }
}

std::pair<callback_id_type, disk_error_code> DiskPort::waitAndGetAnswer(bool is_last_answer) {

    const int max_event_per_request = 1;
    const int min_event_per_request = 1;
    auto event = std::unique_ptr<c_io_event>(new c_io_event);
    while (true) {
        int num_events = io_getevents(ioctx_, min_event_per_request, max_event_per_request,
                                      reinterpret_cast<::io_event *>(event.get()),
                                      &get_events_timeout_);
        if (num_events == 1) { // Success (event count)
            unsigned long long callback_id = event->data;
            BOOST_LOG_TRIVIAL(trace) << "DiskPort::waitAndGetAnswer Completed id: " << callback_id << "; Res: "
                                     << static_cast<signed long>(event->res) << " numev: " << num_events;
            break;
        } else if (num_events == 0) { // Timeout
            BOOST_LOG_TRIVIAL(trace) << "DiskPort::waitAndGetAnswer io_getenvent timeout: " << num_events << " numev: " << num_events; // TODO fix
            if (stop_working_.load() && is_last_answer) {
                throw diskPortInterruptWaitException();
            }

        } else if (num_events < 0) { // Error
            BOOST_LOG_TRIVIAL(trace) << "DiskPort::waitAndGetAnswer error io_getevents: "
                                     << std::error_condition(-num_events, std::generic_category()).message();
            throw std::system_error(-num_events, std::system_category(), "Error getting io_getenvent: ");
        } else {
            BOOST_LOG_TRIVIAL(trace) << "DiskPort::waitAndGetAnswer io_getevents unknow error: " << num_events;
        }

    }

    return {event->data, static_cast<signed long>(event->res)};
}


void DiskPort::shutdown() {
    BOOST_LOG_TRIVIAL(trace) << "DiskPort shutdown called";
    stop_working_.store(true); // Stop endless loop
}



