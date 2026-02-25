 
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

#define INIT_POSX 4
#define INIT_POSY 1

//○ ●

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
    
    std::vector<std::wstring> board = {
        L"    A  B  C  D  E  F  G  H  I  J  K  L  M  N  O",
        L"  +---------------------------------------------+",
        L" 1| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        L" 2| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        L" 3| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        L" 4| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        L" 5| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        L" 6| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        L" 7| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        L" 8| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        L" 9| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        L"10| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        L"11| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        L"12| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        L"13| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        L"14| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        L"15| +  +  +  +  +  +  +  +  +  +  +  +  +  +  + |",
        L"  +---------------------------------------------+"
        };
    std::queue<Packet> messageQueue;
    std::vector<std::string> chat;
    Client* client;
    Server* server;

    std::thread recvThread;
    std::thread sendThread;

    bool sendFlag;
    bool recvFlag;
    bool turnFlag;

    void SettingClient();
public:
    void InitClient(Client* client);
    void InitServer(Server* client);

    void DrawMap();
    void DrawBoard();
    void HandleMessageQueue();
    int PlaceStone(int x, int y, int sender);
};

#endif // GAMESCENE_H