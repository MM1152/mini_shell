#include "../stdafx.h"

#include <sys/socket.h>
#include <thread>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <future>

class Client {
private:
    char buffer[1024];
    int sock;
    bool connection;
    sockaddr_in server { };  

    void ReConnected();
    
    public:
    Client();
    ~Client();
    void Connected(std::promise<int> p);
    void SendData(char* msg);
    char* RecvData();
};