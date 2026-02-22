#include "GameScene.h"

void GameScene::SettingClient()
{
        
}

void GameScene::InitClient(Client *client)
{
    this->client = client;

    recvThread = std::thread(&Client::RecvData, this->client);

    recvThread.join();
}

void GameScene::InitServer(Server *server)
{
    this->server = server;

    while(1) {
    }
}

void GameScene::DrawMap()
{
    while(1)
    {
        Utils::ClearScreen();
        std::cout << "채팅창" << std::endl;
    }
        

}

