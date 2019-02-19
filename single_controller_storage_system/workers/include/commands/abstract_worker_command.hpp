#pragma once

#include "iworker_command.hpp"

namespace gorynych {
    namespace workers {
        class AbstractWorkerCommand : public IWorkerCommand {
        public:
            /***
             *
             * @param type_
             */
            AbstractWorkerCommand(const WorkerCommandType type_);

        protected:
            const WorkerCommandType type_;

        };


    }
}

