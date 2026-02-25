
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
#include <queue>

#define BUFFER_SIZE 1024
#define MSG_SIZE 64

struct Packet {
    short packetId;
    short sender = 0;
    bool turnFlag;
    bool changeTurn;
    char buffer[BUFFER_SIZE];
};

class Socket {
    protected:
        std::atomic<bool> stopFlag { false };

        Packet sendPack;
        Packet recvPack;

        int sock;
        sockaddr_in* socketAddress;
    public:
        Socket() = default;
        virtual ~Socket();

        virtual void Send(std::queue<Packet>* messageQueue, bool* flag, std::vector<std::vector<int>>& board);
        void Receive(std::queue<Packet>* messageQueue, bool* flag);
};
#endif // SOCKET_H