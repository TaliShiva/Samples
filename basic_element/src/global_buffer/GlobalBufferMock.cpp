/**
 * Project Gorynych
 * @version 0.1
 */


#include <fstream>
#include <random>
#include "../../include/global_buffer/GlobalBufferMock.hpp"

GlobalBufferMock::GlobalBufferMock(std::shared_ptr<DiskPerformer> disk_performer)
        : disk_performer(std::move(disk_performer)), offset(0) {}

GlobalBufferMock::~GlobalBufferMock() {
    if (global_buffer_mock_thread_.joinable()) {
        global_buffer_mock_thread_.join();
    }
}

void GlobalBufferMock::startPushInDiskPerformerQueue() {
    global_buffer_mock_thread_ = std::thread(&GlobalBufferMock::waitAndPushInDiskPerformerQueue, this);
}

void GlobalBufferMock::waitAndPushInDiskPerformerQueue() {
    while (!list_of_load_profiles_.empty()) {
        auto length_of_pause = list_of_load_profiles_.front().length_of_pause;
        disk_performer->waitUntilReadyToReceive();
        disk_performer->pushSolidDataChain(list_of_load_profiles_.front().solid_data_chain);
        list_of_load_profiles_.pop_front();
        std::this_thread::sleep_for(length_of_pause);
    }
}

void GlobalBufferMock::initTestData(const LoadParameters &load_parameters) {
    if (is_global_buffer_mock_init_) {
        throw std::logic_error("attempt to reinitialize");
    }
    for (auto &loads: load_parameters.vector_of_load_templates) {
        for (unsigned long i = 0; i < loads.first; i++) {
            for (auto &it: loads.second) {
                list_of_load_profiles_.emplace_back(LoadProfile(it.read_or_write,
                                                                createSolidDataChain(it),
                                                                it.length_of_pause));
            }
        }
    }
    is_global_buffer_mock_init_.store(true);
}

boost::crc_32_type::value_type GlobalBufferMock::getCheckSum() {
    const std::string file_name = "Eeheilaitaiquahmovoh9gohdan5chaipi0aiW5c";
    std::ofstream input(file_name);
    for (auto &load_profile: list_of_load_profiles_) {
        for (auto &solid_data: load_profile.solid_data_chain->solid_datas) {
            for (auto &data_atom: solid_data->data_atoms) {
                input.seekp(data_atom->physical_region.disk_offset, input.beg); //set pointer to the place of record DataAtom
                input.write(reinterpret_cast<char*>(data_atom->raw_data_write_ptr->data.data()), //write DataAtom
                            data_atom->physical_region.disk_length);
            }
        }
    }
    input.close();

    std::ifstream output(file_name);
    output.seekg(0, output.end);
    size_t size = output.tellg();
    payload_data_vector buffer(size, ' ');
    output.seekg(0);
    output.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
    output.close();

    std::remove(file_name.c_str());
    boost::crc_32_type sum;
    sum.process_bytes(buffer.data(), buffer.size());
    return sum.checksum();
}


unsigned int GlobalBufferMock::getRandomOffset() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 3);
    return 4096 * dis(gen);
}


std::shared_ptr<SolidData> GlobalBufferMock::createSolidData(const LoadTemplate &load_template) {
    std::ifstream file("/dev/urandom");
    unsigned long long raw_data_offset = 0;
    unsigned int raid_id = 5;
    unsigned int raid_disk_number = 1;
    std::vector<std::shared_ptr<DataAtom>> data_atoms_vector;
    for (unsigned long i = 0; i < load_template.number_of_data_atoms; i++) {
        auto raw_data_write = std::make_shared<RawDataWrite>(load_template.length_of_data);
        payload_data_vector buffer(load_template.length_of_data, ' ');
        file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
        raw_data_write->data.insert(raw_data_write->data.begin(),
                                    buffer.begin(),
                                    buffer.end());
        PhysicalRegion physical_region(raid_id,
                                       raid_disk_number,
                                       offset,
                                       load_template.length_of_data);
        offset += load_template.length_of_data;

        auto data_atom = std::make_shared<DataAtom>(raw_data_offset,
                                                    physical_region,
                                                    raw_data_write);
        data_atoms_vector.emplace_back(data_atom);
    }
    offset += getRandomOffset();
    file.close();
    return std::make_shared<SolidData>(std::move(data_atoms_vector));
}

std::shared_ptr<SolidDataChain> GlobalBufferMock::createSolidDataChain(const LoadTemplate &load_template) {
    std::vector<std::shared_ptr<SolidData>> solid_data_vector;
    for (unsigned long i = 0; i < load_template.number_of_solid_data; i++) {
        solid_data_vector.emplace_back(createSolidData(load_template));
    }
    return std::make_shared<SolidDataChain>(std::move(solid_data_vector));
}
