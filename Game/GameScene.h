 
#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../stdafx.h"
#include <vector>
#include "Server.h"
#include "Client.h"
#include "../Utils.h"

class GameScene {
private:
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