#include "../stdafx.h"

#include <sys/socket.h>
#include <thread>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

class Server{
private:
    sockaddr_in server {};
    sockaddr_in client {};    

    int server_fd;
    int client_fd;

    void CreateSocket();
    void BindAdress();
    void ConnectClient();
    void Accept();
    int Check();
public:
    int Open();
    ~Server();
};