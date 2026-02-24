#include "Socket.h"
#include <string>
#include <termios.h>
#include "../Utils.h"
Socket::~Socket()
{
    delete socketAddress;
}

void Socket::Send(std::vector<Packet>* messageQueue, bool* flag)
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
            Packet pack;
            
            char ch;
            int pointer = 0;
            while((ch = getchar()) != '\n' && ch != EOF){
                pack.buffer[pointer++] = ch;
            }
            pack.buffer[pointer] = '\0';

            if(ch == '\n') {
                std::vector<std::string> split = Utils::SplitString(pack.buffer, ' ');
                if(split.size() > 1 && ( split[0][0] >= 'A' && split[0][0] <= 'O') && ( std::stoi(split[1]) >= 1 && std::stoi(split[1]) <= 15)) {
                    pack.packetId = 1001; // 게임에 사용되는 데이터 패킷 아이디
                }
                else {
                    pack.packetId = 1002; // 메세지용 패킷  아이디
                }

                if(strcmp(pack.buffer, "exit") == 0) {
                    stopFlag = true;
                    break;
                }

                if(send(sock, &pack, MSG_SIZE, 0) <= 0) {
                    stopFlag = true;
                    break;
                }

                messageQueue->push_back(pack);
            }
        }
        // std::string str(msg);
    }
    *flag = stopFlag;
}

void Socket::Receive(std::vector<Packet>* messageQueue, bool* flag)  
{
    Packet pack;
    while(!stopFlag) {
        if(recv(sock, &pack, BUFFER_SIZE + 2, 0) <= 0) {
            stopFlag = true;
            break;
        }

        std::string str(pack.buffer);
        if(strcmp(pack.buffer, "exit") == 0) {
            stopFlag = true;
            break;
        }
        messageQueue->push_back(pack);
    }
    std::cout << "통신 종료됌" << std::endl;
    *flag = stopFlag;
}
