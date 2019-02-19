//
// Created by boa on 13.03.17.
//

#pragma once

#include "abstract_command.hpp"

namespace gorynych {
    namespace transport {
        /**
         * @class RemoveIscsiTargetCommand - команда удаления таргета, для передачи средствами нашего траннспорта
         */
        class RemoveIscsiTargetCommand : public AbstractCommand {
        public:
            /**
             * @brief RemoveIscsiTargetCommand @see documentation AbstractCommand
             */
            RemoveIscsiTargetCommand();

            RemoveIscsiTargetCommand(protobuf::Command command);

        private:
            std::string targetName_;
        public:
            const std::string &targetName() const;

            void setTargetName(const std::string &targetName);
        };
    }
}

