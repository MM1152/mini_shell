#include "TitleScene.h"

void TitleScene::ClearScreen()
{
    std::cout << "\033[2J\033[H" << std::flush;
}

TitleScene::TitleScene()
{
    curText = selectText;
    textArraySize = 2;
}

TitleScene::~TitleScene()
{
    if(server != nullptr)
        delete server;
    if(client != nullptr) 
        delete client;
}

int TitleScene::ChangeText(int input)
{
    if(curText == selectText) {
        if(input == 50) {
            return -1;
        }
        if(input == 49) {
            curText = createorjoinText;
            textArraySize = 2;
            return 1;
        }
    }

    if(curText == createorjoinText) {
        if(input == 49) {
            curText = &waitforJoinRoom;
            textArraySize = 1;
            JoinRoom();
            return 1;
        }
        if(input == 50) {
            curText = &waitforUserText;
            textArraySize = 1;
            CreateRoom();
            return 1;
        }
    }
    return -1;
}



void TitleScene::ShowTitlePanel()
{
    ClearScreen();
    std::cout << titleText << std::endl;
    
    for(int i = 0; i < textArraySize; i++) {
        std::cout << curText[i] << std::endl;
    }
}

void TitleScene::CreateRoom()
{
    server = new Server();
    if(server->Open() == 1) {
        curText = &matchingText;
    }
    
}

void TitleScene::JoinRoom()
{
    client = new Client();
    if(client->Connected() == 1) {
        curText = &matchingText;
    }
}
