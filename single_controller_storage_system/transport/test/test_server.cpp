

#include "../include/transport_api.hpp"
#include "../include/server.hpp"

using namespace gorynych::transport;

int main(int argc, char* argv[])
{
    std::string file = "/tmp/gorynych_control.sock";
    Listener listener(file);
    listener.listen();

}
