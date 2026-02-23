 
#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../stdafx.h"
#include "../Utils.h"
#include <thread>
#include "Server.h"
#include "Client.h"
#include "Socket.h"
#include <vector>
#include "MainGame.h"

class GameScene {
private:
    std::vector<std::string> messageQueue;
    Client* client;
    Server* server;

    std::thread recvThread;
    std::thread sendThread;
    
    void SettingClient();
public:
    void InitClient(Client* client);
    void InitServer(Server* client);

    void DrawMap();
};

#endif // GAMESCENE_H