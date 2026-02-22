#include "TitleScene.h"
#include <future>

TitleScene::TitleScene(GameScene* gameScene)
{
    curText = selectText;
    this->gameScene = gameScene;
    gameScene = new GameScene();
    textArraySize = 2;
}

TitleScene::~TitleScene()
{
    if(server != nullptr)
        delete server;
    if(client != nullptr) 
        delete client;
    if(gameScene != nullptr)
        delete gameScene;

    isConnection = false;
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
    Utils::ClearScreen();
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
        gameScene->InitServer(server);
        isConnection = true;
    }
}

void TitleScene::JoinRoom()
{
    client = new Client();
    std::promise<int> p;
    std::future<int> result = p.get_future();
    std::thread t(&Client::Connected, client, std::move(p));

    curText = &duringMatcing;
    ShowTitlePanel();
    t.join();
    
    if(result.get() == 1) {
        curText = &matchingText;
        gameScene->InitClient(client);
        ShowTitlePanel();
        isConnection = true;
    }  
    else {
        curText = createorjoinText;
        ShowTitlePanel();
    }
}
