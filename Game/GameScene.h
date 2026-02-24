 
#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../stdafx.h"
#include "../Utils.h"
#include <thread>
#include <queue>
#include "Server.h"
#include "Client.h"
#include "Socket.h"
#include <vector>
#include "MainGame.h"

class GameScene {
private:
    std::vector<std::vector<int>> backgroundBoard {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    
    std::vector<std::string> board = {
        "    A  B  C  D  E  F  G  H  I  J  K  L  M  N  O",
        "  +---------------------------------------------+",
        " 1| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        " 2| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        " 3| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        " 4| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        " 5| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        " 6| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        " 7| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        " 8| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        " 9| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        "10| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        "11| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        "12| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        "13| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        "14| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        "15| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        "  +---------------------------------------------+"
        };
    std::queue<Packet> messageQueue;
    Client* client;
    Server* server;

    std::thread recvThread;
    std::thread sendThread;

    bool sendFlag;
    bool recvFlag;
    
    void SettingClient();
public:
    void InitClient(Client* client);
    void InitServer(Server* client);

    void DrawMap();
    void DrawBoard();
    void HandleMessageQueue(std::vector<std::string>& chat);
};

#endif // GAMESCENE_H