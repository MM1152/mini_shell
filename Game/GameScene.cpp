#include "GameScene.h"

void GameScene::SettingClient()
{
        
}

void GameScene::InitClient(Client *client)
{
    this->client = client;

    sendThread = std::thread(&Client::Send, this->client, &messageQueue, &sendFlag);
    recvThread = std::thread(&Client::Receive, this->client, &messageQueue, &recvFlag);
}

void GameScene::InitServer(Server *server)
{
    this->server = server;

    sendThread = std::thread(&Server::Send, this->server, &messageQueue, &sendFlag);
    recvThread = std::thread(&Server::Receive, this->server, &messageQueue, &recvFlag);
}

void GameScene::DrawMap()
{
    int prevQueueSize = messageQueue.size();

    while(1) {

        if(messageQueue.size() != prevQueueSize) {
            prevQueueSize = messageQueue.size();
            struct winsize ws = Utils::GetTerminalSize();
            int space = ws.ws_row - board.size() - 2;

            Utils::ClearScreen();
            DrawBoard();
            std::cout << "-------------------[ 채팅창 ]--------------------" << std::endl;

            for(int i = 0; i < messageQueue.size(); i++) {
                std::cout << messageQueue[i] << std::endl;
            }

            for(int i = 0; i < space - messageQueue.size(); i++) {    
                std::cout << std::endl;
            }

            if(messageQueue.size() >= space - 1) {
                messageQueue.erase(messageQueue.begin());
            }
        }

        if(recvFlag && sendFlag) {
            std::cout << "GameScene Loop Finish" << std::endl;
            break;
        }
    }
    if(sendThread.joinable()) sendThread.join();
    if(recvThread.joinable()) recvThread.join();
}

void GameScene::DrawBoard()
{
    for(int i = 0 ; i < board.size(); i++){
        std::cout << board[i] << std::endl;
    }
}
