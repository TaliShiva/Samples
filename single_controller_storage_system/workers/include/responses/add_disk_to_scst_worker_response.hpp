//
// Created by boa on 15.03.17.
//

#pragma once

#include "abstract_worker_response.hpp"

namespace gorynych {
    namespace workers {

        class AddDiskToScstWorkerResponse : public AbstractWorkerResponse {
        public:
            /**
             *
             * @param success
             * @param systemErrorMessage
             * @param logicErrorMessage
             */
            AddDiskToScstWorkerResponse(const bool success,
                                        const std::string &systemErrorMessage = "",
                                        const std::string &logicErrorMessage = "");


        };


    }
}

