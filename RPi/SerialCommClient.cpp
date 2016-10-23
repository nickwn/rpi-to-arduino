#include <iostream>
#include <string>
#include <vector>
#include <getopt.h>
#include <boost/asio.hpp>
#include "rs232.h"

#define _WIN32_WINDOWS

using boost::asio::ip::tcp;

static struct option long_options[] =
{
  {"host", required_argument, 0, 'h'},
  {"port", required_argument, 0, 'p'},
  {"serial", required_argument, 0, 's'},
  {0, 0, 0, 0}
};


int main (int argc, char* argv[])
{
  char* host = nullptr;
  char* port = nullptr;
  int serial = -1;

  std::string usage = "Usage: \n" + std::string(argv[0]) + " -host <host> -port <port> -serial <serial>";
  int c = 0;
  int option_index = 0;
  while((c = getopt_long(argc, argv, "h:p:s:", long_options, &option_index)) != -1)
  {
    switch(c)
    {
    case 'h':
      host = optarg;
      break;
    case 'p':
      port = optarg;
      break;
    case 's':
      serial = atoi(optarg);
      break;
    case '?':
      return -1;
    default:
      abort();
    }
  }

  if(host == nullptr || port == nullptr || serial == -1)
  {
    std::cerr << usage << std::endl;
  }

  char mode[]={'8','N','1',0};
  int bdrate = 9600;
  if(RS232_OpenComport(serial, bdrate, mode))
  {
    std::cerr << "Could not open port " + serial << std::endl;
    return -1;
  }

  try
  {
    boost::asio::io_service io_service;
    tcp::socket s(io_service);
    tcp::resolver resolver(io_service);
    boost::asio::connect(s, resolver.resolve({host, port}));

    while(true)
    {
      std::string in;
      boost::asio::read(s, boost::asio::buffer(in, 256));

      size_t pos;
      const char* split[4];
      for(int i = 0; (pos=in.find(";")) != std::string::npos; i++)
      {
        split[i] = in.substr(0, pos).c_str();
        in = in.substr(pos+1);
      }

      if(split[0] == "true")
      {
        std::string msg = ";" + (char) atoi(split[1]) + (char) atoi(split[2]) + (char) atoi(split[3]);
        RS232_cputs(serial, msg.c_str());
      }
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
}
