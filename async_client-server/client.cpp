//
//


#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 8001);

int main(int argc, char* argv[])
{
  try
  {
//    if (argc != 2)
//    {
//      std::cerr << "Usage: client <host>" << std::endl;
//      return 1;
//    }

    boost::asio::io_service io_service;

    //tcp::resolver resolver(io_service);
    //tcp::resolver::query query(argv[1], "daytime");
    //tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    tcp::socket socket(io_service);
    socket.connect(ep);
    //boost::asio::connect(socket, ep);//захардкожено

    for (;;)
    {
      boost::array<char, 128> buf;
      boost::system::error_code error;

      size_t len = socket.read_some(boost::asio::buffer(buf), error);

      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      std::cout.write(buf.data(), len);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}