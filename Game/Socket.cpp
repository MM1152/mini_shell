#include "Socket.h"
#include <string>
#include <termios.h>
#include <cctype>
#include <algorithm>

#include "../Utils.h"
Socket::~Socket()
{
    delete socketAddress;
}

void Socket::Send(std::queue<Packet>* messageQueue, bool* flag, std::vector<std::vector<int>>& board)
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
            char ch;
            int pointer = 0;
            while((ch = getchar()) != '\n' && ch != EOF){
                sendPack.buffer[pointer++] = ch;
            }
            sendPack.buffer[pointer] = '\0';

            if(ch == '\n') {
                std::vector<std::string> split = Utils::SplitString(sendPack.buffer, ' ');
                if(split.size() > 1 && ( split[0][0] >= 'A' && split[0][0] <= 'O') &&
                   std::all_of(split[1].begin(), split[1].end(), ::isdigit) &&
                   std::stoi(split[1]) >= 1 && std::stoi(split[1]) <= 15) {
                    sendPack.packetId = 1001; // 게임에 사용되는 데이터 패킷 아이디
                    // memset(pack.buffer, '\0', sizeof(pack.buffer));
                    // pack.buffer[0] = split[0][0];
                    // pack.buffer[1] = split[1][0];
                }
                else {
                    sendPack.packetId = 1002; // 메세지용 패킷  아이디
                }

                if(strcmp(sendPack.buffer, "exit") == 0) {
                    stopFlag = true;
                    break;
                }

                bool changeTurn = sendPack.turnFlag && sendPack.packetId == 1001 && board[std::stoi(split[1])][split[0][0] - 'A'] == 0;
                sendPack.changeTurn = changeTurn;

                if(send(sock, &sendPack, MSG_SIZE, 0) <= 0) {
                    stopFlag = true;
                    break;
                }
                messageQueue->push(sendPack);
                
                if(changeTurn) {
                    sendPack.turnFlag = false;
                }

            }
        }
        // std::string str(msg);
    }
    *flag = stopFlag;
}

void Socket::Receive(std::queue<Packet>* messageQueue, bool* flag)  
{
    while(!stopFlag) {
        if(recv(sock, &recvPack, BUFFER_SIZE + 2, 0) <= 0) {
            stopFlag = true;
            break;
        }

        std::string str(recvPack.buffer);
        if(strcmp(recvPack.buffer, "exit") == 0) {
            stopFlag = true;
            break;
        }

        recvPack.sender = 1;
        messageQueue->push(recvPack);

        if(recvPack.packetId == 1001 && recvPack.changeTurn) {
            sendPack.turnFlag = true;
        }
    }
    std::cout << "통신 종료됌" << std::endl;
    *flag = stopFlag;
}
