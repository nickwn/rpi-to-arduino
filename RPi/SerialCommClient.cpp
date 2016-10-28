#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <getopt.h>
#include <boost/asio.hpp>
#include <thread>
#include "rs232.h"

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
  const char* host = "";
  const char* port = "";
  int serial = -1;

  std::string usage = "Usage: \n" + std::string(argv[0]) + " --host <host> --port <port> --serial <serial>";
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
      serial = std::atoi(optarg);
      break;
    case '?':
      return -1;
    default:
      abort();
    }
  }

  if(host == "" || port == "" || serial == -1)
  {
    std::cerr << usage << std::endl;
  }


  std::cout << "Opening serial port " << serial << "..." << std::endl;

  char mode[]={'8','N','1',0};
  int bdrate = 9600;
  if(RS232_OpenComport(serial, bdrate, mode))
  {
    std::cerr << "Could not open port " << serial << std::endl;
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
      boost::asio::streambuf buffer;
      boost::asio::read_until(s, buffer, '\n');
      std::istream str(&buffer);
      std::string in;
      std::getline(str, in);
      std::cout << "Recieved message: " << in << std::endl;

      std::vector<std::string> split;
      std::stringstream ss(in);
      std::string tok;
      while(getline(ss, tok, ';'))
      {
        split.push_back(tok);
      }


      if(split[0] == "true")
      {
        std::cout << "Found target" << std::endl;
        char dist = (char) std::atoi(split[1].c_str());
        char azimuth = (char) std::atoi(split[2].c_str());
        char altitude = (char) std::atoi(split[3].c_str());
        std::string msg({';', dist, azimuth, altitude});
        std::cout << "Sending message: " << msg << std::endl;
      }
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
}
