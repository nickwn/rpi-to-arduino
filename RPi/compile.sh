#!/bin/bash
echo "Compling TestServer"
g++ TestServer.cpp -o TestServer -std=c++11 -lboost_system
echo "Compiling SerialCommClient"
g++ SerialCommClient.cpp rs232.c -o SerialCommClient -std=c++11 -pthread -lboost_system -w
