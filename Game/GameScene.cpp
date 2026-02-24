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
    std::vector<std::string> chat;
    int prevQueueSize = chat.size() - 1;
    while(1) {
        if(!messageQueue.empty())
            HandleMessageQueue(chat);

        if(chat.size() != prevQueueSize) {
            prevQueueSize = chat.size();
            struct winsize ws = Utils::GetTerminalSize();
            int space = ws.ws_row - board.size() - 2;

            Utils::ClearScreen();
            DrawBoard();
            std::cout << "-------------------[ 채팅창 ]--------------------" << std::endl;

            for(int i = 0; i < chat.size(); i++ ){
                std::cout << chat[i] << std::endl;
            }

            for(int i = 0; i < space - chat.size() - 1; i++) {    
                std::cout << std::endl;
            }

            std::cout << ">>>>>>>>> 착수 방법 예시 ) A 10  <<<<<<<<<" << std::endl;
            if(chat.size() >= space - 1) {
                chat.erase(chat.begin());
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

void GameScene::HandleMessageQueue(std::vector<std::string>& chat)
{
    while(!messageQueue.empty()) {
        Packet packet = messageQueue.front();
        messageQueue.pop();
        
        if(packet.packetId == 1001) {
            std::vector<std::string> split = Utils::SplitString(packet.buffer, ' ');
            char placeX = split[0][0];
            int placeY = std::stoi(split[1]);
            chat.push_back(std::string(packet.sender == 0 ? "[ 내가 착수한 위치 ] { " : "[ 상대방이 착수한 위치 ] : [ ") + placeX + ", " + std::to_string(placeY) + " ]");
        }
        else {
            chat.push_back(std::string(packet.sender == 0 ? "[ 내가 보낸 메세지 ] : " : "[ 상대방 ] : ") + packet.buffer);
        }
    }
}
