#ifndef SERVER_H
#define SERVER_H

#include "../stdafx.h"
#include "Socket.h"


class Server : public Socket {
private:
    sockaddr_in client {};    

    int server_fd;
    int port;
    
    void CreateSocket();
    void BindAdress();
    void ConnectClient();
    void Accept();
    int Check();
public:
    void Open(std::promise<int>* p);
    Server(int port);
    ~Server() override;
};

#endif // SERVER_H