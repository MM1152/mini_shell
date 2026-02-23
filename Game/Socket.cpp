#include "Socket.h"
#include <string>

Socket::~Socket()
{
    delete socketAddress;
}

void Socket::Send(std::vector<std::string>* messageQueue)
{
    while(!stopFlag) {
        std::cin >> msg;
        if(send(sock, msg, MSG_SIZE, 0) <= 0) {
            stopFlag = true;
            break;
        }
        std::string str(msg);
        messageQueue->push_back("[내가 보낸 메세지] : " + str);
    }
}

void Socket::Receive(std::vector<std::string>* messageQueue)  
{
    while(!stopFlag) {
        if(recv(sock, buffer, BUFFER_SIZE, 0) <= 0) {
            stopFlag = true;
            break;
        }
        std::string str(buffer);
        messageQueue->push_back("[상대방] : " + str);
    }
    std::cout << "통신 종료됌" << std::endl;
}
