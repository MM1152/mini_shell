#include "GameScene.h"

void GameScene::SettingClient()
{
        
}

void GameScene::InitClient(Client *client)
{
    this->client = client;

    sendThread = std::thread(&Client::Send, this->client, &messageQueue);
    recvThread = std::thread(&Client::Receive, this->client, &messageQueue);
}

void GameScene::InitServer(Server *server)
{
    this->server = server;

    sendThread = std::thread(&Server::Send, this->server, &messageQueue);
    recvThread = std::thread(&Server::Receive, this->server, &messageQueue);
}

void GameScene::DrawMap()
{
    int prevQueueSize = messageQueue.size();
    while(1) {
        if(messageQueue.size() != prevQueueSize) {
            prevQueueSize = messageQueue.size();
            struct winsize ws = Utils::GetTerminalSize();

            int space = ws.ws_row - messageQueue.size() - 1;

            Utils::ClearScreen();
            std::cout << "채팅창" << std::endl;

            for(int i = 0; i < messageQueue.size(); i++) {
                std::cout << messageQueue[i] << std::endl;
            }

            for(int i = 0; i < space; i++) {    
                std::cout << std::endl;
            }

            if(messageQueue.size() >= space - 1) {
                messageQueue.erase(messageQueue.begin());
            }
        }
    }


    recvThread.join();
    sendThread.join();

    exit(1);
}

