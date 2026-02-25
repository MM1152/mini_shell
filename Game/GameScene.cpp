#include "GameScene.h"

int GameScene::CheckBoard(int x, int y, int sender, std::pair<int, int> dir)
{
    int count = 0;
    
    while(true) {
        x = x + dir.second;
        y = y + dir.first;

        if(x < 0 || y < 0 || x >= backgroundBoard.size() || y >= backgroundBoard.size()) {
            break;
        }

        if(backgroundBoard[y][x] !=  sender + 1) {
            break;
        }

        count++;
    }

    return count;
}

void GameScene::SettingClient()
{
        
}

void GameScene::InitClient(Client *client)
{
    this->client = client;

    sendThread = std::thread(&Client::Send, this->client, &messageQueue, &sendFlag, std::ref(backgroundBoard));
    recvThread = std::thread(&Client::Receive, this->client, &messageQueue, &recvFlag);

    turnFlag = false;
}

void GameScene::InitServer(Server *server)
{
    this->server = server;

    sendThread = std::thread(&Server::Send, this->server, &messageQueue, &sendFlag, std::ref(backgroundBoard));
    recvThread = std::thread(&Server::Receive, this->server, &messageQueue, &recvFlag);
    
    turnFlag = true;
}

void GameScene::DrawMap()
{
    int prevQueueSize = messageQueue.size() - 1;
    bool first = true;
    while(1) {
        if(!messageQueue.empty() || first) {
            HandleMessageQueue();

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

            std::cout << " 착수 방법 예시 ) A 10 " << (turnFlag ? "( 내 차례 )" :"( 상대 차례 )") << std::endl;
            if(chat.size() >= space - 1) {
                chat.erase(chat.begin());
            }
            first = false;
        }
        if(winner != -1) {
            std::cout << "승자 정해짐" << std::endl;
            recvFlag = true;
            sendFlag = true;
            server->stopFlag = true;
            client->stopFlag = true;
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
        std::wcout << board[i] << std::endl;
    }
}

void GameScene::HandleMessageQueue()
{
    while(!messageQueue.empty()) {
        Packet packet = messageQueue.front();
        
        if(packet.packetId == 1001 && packet.turnFlag) {
            std::vector<std::string> split = Utils::SplitString(packet.buffer, ' ');
            char placeX = split[0][0];
            int placeY = std::stoi(split[1]);

            if(PlaceStone(placeX - 'A', placeY, packet.sender) != -1){
                chat.push_back(std::string(packet.sender == 0 ? "[ 내가 착수한 위치 ] [ " : "[ 상대방이 착수한 위치 ] : [ ") + placeX + ", " + std::to_string(placeY) + " ]");
                if(packet.sender == 1 && packet.changeTurn && !turnFlag) turnFlag = true;
                else if(packet.sender == 0 && packet.changeTurn && turnFlag) turnFlag = false;
            }
        }
        else if(packet.packetId == 1002){
            chat.push_back(std::string(packet.sender == 0 ? "[ 내가 보낸 메세지 ] : " : "[ 상대방 ] : ") + packet.buffer);
        }
        
        messageQueue.pop();
    }
}

int GameScene::CheckWin(int x, int y, int sender)
{
    int count = 0;
    for(int i = 0; i < 4; i++) {
        count += CheckBoard(x, y, sender, direction[i]);
        count += CheckBoard(x, y, sender, direction[i + 4]);
        count += 1;
        if(count >= 5) {
            return 1;
        }
        count = 0;
    }
    return -1;
}

int GameScene::PlaceStone(int x, int y, int sender)
{
    if(backgroundBoard[y - 1][x] != 0 && sender == 0) chat.push_back("[ 이미 돌이 놔있는 지역입니다. ]");
    if(backgroundBoard[y - 1][x] != 0) return -1;

    backgroundBoard[y - 1][x] = sender + 1;
    board[INIT_POSY + y][INIT_POSX + x * 3] = sender == 0 ? 'O' : 'X';

    if(CheckWin(x, y - 1, sender) == 1) {
        winner = sender;
        return 1;
    }
    return 1;
}
