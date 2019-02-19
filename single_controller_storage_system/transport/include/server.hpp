
#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "packet.hpp"
#include "network.hpp"
#include "transport_api.hpp"
#include "../../logic_module/include/logic_module.hpp"

namespace gorynych {
    namespace transport {
        using namespace boost::asio;
        using  namespace logic;
        class Listener {
        private:
            io_service ioservice_;
            std::string file_;
            Logic logic_;
        public:
            Listener(std::string file);
            void listen();
            std::string handleRequest(std::string data);
            void handleConnections();
        };

    }
}