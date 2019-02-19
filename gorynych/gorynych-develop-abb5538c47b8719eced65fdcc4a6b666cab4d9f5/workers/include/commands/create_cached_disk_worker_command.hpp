#pragma once

#include "abstract_worker_command.hpp"

#include <string>

namespace gorynych {
    namespace workers {
        enum class CachingAlgorithm {
            LRU,
            FIFO,
            Random
        };

        enum class CachingMode {
            Writeback,
            Writethrough
        };

        class CreateCachedDiskWorkerCommand: public AbstractWorkerCommand {
        public:
            CreateCachedDiskWorkerCommand(const std::string &baseDevicePath,
                                          const std::string &cachingDevicePath,
                                          CachingAlgorithm cachingAlgorithm,
                                          CachingMode cachingMode);
            const std::string baseDevicePath() const;
            const std::string cachingDevicePath() const;
            const CachingAlgorithm cachingAlgorithm() const;
            const CachingMode cachingMode() const;
        private:
            const std::string baseDevicePath_;
            const std::string cachingDevicePath_;
            const CachingAlgorithm cachingAlgorithm_;
            const CachingMode cachingMode_;
        };
    }
}
