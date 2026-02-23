
#ifndef SOCKET_H
#define SOCKET_H

#include "../stdafx.h"
#include <sys/socket.h>
#include <thread>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <future>
#include <vector>

#define BUFFER_SIZE 1024
#define MSG_SIZE 64

class Socket {
    protected:
        std::atomic<bool> stopFlag { false };
        char buffer[BUFFER_SIZE];
        char msg[MSG_SIZE];

        int sock;
        sockaddr_in* socketAddress;
    public:
        Socket() = default;
        virtual ~Socket();

        void Send(std::vector<std::string>* messageQueue);
        void Receive(std::vector<std::string>* messageQueue);
};
#endif // SOCKET_H