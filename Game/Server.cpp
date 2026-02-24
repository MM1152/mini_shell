#include "Server.h"
#include "../Define.h"
void Server::CreateSocket()
{
    socketAddress = new sockaddr_in();
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    socketAddress->sin_family = AF_INET;
    socketAddress->sin_port = htons(port);
    socketAddress->sin_addr.s_addr = INADDR_ANY;
}

void Server::BindAdress()
{
    if(bind(server_fd, (sockaddr*)socketAddress, sizeof(sockaddr_in)) < 0) {
        if(errno == EADDRINUSE) {
            throw "Port aleady in user";
        }
        else {
            throw "fail to bind";
        }
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
    sock = accept(server_fd, (sockaddr*)&client, &client_len);
    if(sock < 0) {
        throw "fail to accept";
    }
}

int Server::Check()
{
    std::string msg = "checkConnect";
    int result = send(sock, msg.c_str(), sizeof(msg), 0);
    return result;
}

void Server::Open(std::promise<int>* p)
{
    try {
        do{
            CreateSocket();
            BindAdress();
            ConnectClient();
            Accept();
            if(Check() >= 0) {
                break;
            }
        }while(1);

        p->set_value(1);
    }
    catch (const char* e) {
        p->set_value(-1);
        std::cout << e << std::endl;
    }

}

Server::Server(int port)
{
    this->port = port;
}

Server::~Server()
{
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    close(server_fd);
    close(sock);
}
