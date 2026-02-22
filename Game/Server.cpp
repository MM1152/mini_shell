#include "Server.h"

void Server::CreateSocket()
{
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    server.sin_family = AF_INET;
    server.sin_port = htons(7777);
    server.sin_addr.s_addr = INADDR_ANY;
}

void Server::BindAdress()
{
    if(bind(server_fd, (sockaddr*)&server, sizeof(server)) < 0) {
        throw "fail to bind";
    }
}

void Server::ConnectClient()
{
    if(listen(server_fd, 1) < 0) {
        throw "fail to connect";
    }
}

void Server::Accept()
{
    socklen_t client_len = sizeof(client);
    client_fd = accept(server_fd, (sockaddr*)&client, &client_len);
    if(client_fd < 0) {
        throw "fail to accept";
    }
}

int Server::Check()
{
    std::string msg = "checkConnect";
    int result = send(client_fd, msg.c_str(), sizeof(msg), 0);
    return result;
}

int Server::Open()
{
    try {
        CreateSocket();
        BindAdress();
        ConnectClient();
        Accept();
        if(Check() <= 0){
            Open();
        }
    }
    catch (const char* e) {
        std::cout << e << std::endl;
    }

    return 1;
}

void Server::Recv()
{
    while(1) {
        if(recv(client_fd, buffer, sizeof(buffer), 0) <= 0) {
            break;
        } 
        std::cout << "Get Message : " << buffer << std::endl;
    }
}

void Server::Send()
{
    char msg[1024];
    while(1) {
        std::cin >> msg;

        if(send(client_fd, msg, sizeof(msg), 0) <= 0) {
            break;
        }
    }
}


Server::~Server()
{
    close(client_fd);
    close(server_fd);
}
