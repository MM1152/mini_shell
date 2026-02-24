#include "Socket.h"
#include <string>
#include <termios.h>
#include "../Utils.h"
Socket::~Socket()
{
    delete socketAddress;
}

void Socket::Send(std::vector<std::string>* messageQueue, bool* flag)
{
    while(!stopFlag) {
        fd_set set;
        struct timeval timeout;
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);

        timeout.tv_sec = 2;
        timeout.tv_usec = 0;

        int rv = select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout);
        if (rv > 0) {
            char ch = getchar();
            if(ch == '\n') {
                if(strcmp(msg.c_str(), "exit") == 0) {
                    stopFlag = true;
                    break;
                }
                if(send(sock, msg.c_str(), MSG_SIZE, 0) <= 0) {
                    stopFlag = true;
                    break;
                }
                
                messageQueue->push_back("[내가 보낸 메세지] : " + msg);
                msg.clear();
            }
            else {
                msg += ch;
            }
        }
        // std::string str(msg);
    }
    *flag = stopFlag;
}

void Socket::Receive(std::vector<std::string>* messageQueue, bool* flag)  
{
    while(!stopFlag) {
        if(recv(sock, buffer, BUFFER_SIZE, 0) <= 0) {
            stopFlag = true;
            break;
        }
        std::string str(buffer);
        if(strcmp(buffer, "exit") == 0) {
            stopFlag = true;
            break;
        }
        messageQueue->push_back("[상대방] : " + str);
    }
    std::cout << "통신 종료됌" << std::endl;
    *flag = stopFlag;
}
