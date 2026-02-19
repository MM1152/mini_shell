#include "../stdafx.h"

#include <sys/socket.h>
#include <thread>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>

class Client {
private:
    int sock;
    sockaddr_in server { };  
public:
    Client();
    ~Client();
    int Connected();
};