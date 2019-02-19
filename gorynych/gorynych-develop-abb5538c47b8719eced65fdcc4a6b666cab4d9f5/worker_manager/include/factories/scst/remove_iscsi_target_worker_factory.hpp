//
// Created by boa on 13.03.17.
//
#pragma once

#include "../abstact_worker_factory.hpp"
#include "../../../../workers/include/commands/remove_iscsi_target_command.hpp"

namespace gorynych {
     namespace worker_manager{
         class RemoveIscsiTargetWorkerFactory : public AbstractWorkerFactory {
         public:
             RemoveIscsiTargetWorkerFactory() {}

             AbstractWorker *createWorker(const unsigned int id) override;

             void init(const RemoveIscsiTargetWorkerCommand &command);

         private:
             const RemoveIscsiTargetWorkerCommand *command_;

         };
     }
 }