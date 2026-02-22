#include "GameScene.h"

void GameScene::SettingClient()
{
        
}

void GameScene::InitClient(Client *client)
{
    this->client = client;

    sendThread = std::thread(&Client::SendData, this->client);
    recvThread = std::thread(&Client::RecvData, this->client);
}

void GameScene::InitServer(Server *server)
{
    this->server = server;

    sendThread = std::thread(&Server::Send, this->server);
    recvThread = std::thread(&Server::Recv, this->server);
}

void GameScene::DrawMap()
{
    std::cout << "채팅창" << std::endl;
    
    recvThread.join();
    sendThread.join();
}

