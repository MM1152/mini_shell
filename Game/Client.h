 
#ifndef CLIENT_H
#define CLIENT_H

#include "Socket.h"
#include "../stdafx.h"
#include <sys/socket.h>
#include <thread>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <future>

class Client : public Socket{
private:
    sockaddr_in server { };  
    void ReConnected();
    bool connection;
public:
    Client();
    ~Client();
    void Connected(std::promise<int> p);
};

#endif // CLIENT_H