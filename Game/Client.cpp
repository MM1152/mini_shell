#include "Client.h"

Client::Client()
{
    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(7777);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
}

Client::~Client()
{
    close(sock);
}

int Client::Connected()
{
    if(connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
        std::cout << "fail to connect" << std::endl;
        return -1;
    }

    return 1;
}