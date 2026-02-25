#include "TitleScene.h"
#include "../Utils.h"
#include <future>
#include <string>
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

int TitleScene::ChangeText(std::string input)
{
    if(curText == selectText) {
        if((int)input[0] == 50) {
            return -1;
        }
        if((int)input[0] == 49) {
            curText = createorjoinText;
            textArraySize = 2;
            return 1;
        }
    }
    else if(curText == createorjoinText) {
        std::vector<std::string> splitdatas = Utils::SplitString(input, ' ');
        if(splitdatas.size() == 1) {
            port = 7777;
        }
        else {
            port = std::stoi(splitdatas[1]);
        }

        if((int)input[0] == 49) {
            JoinRoom();
            return 1;
        }
        if((int)input[0] == 50) {
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
    server = new Server(port);
    std::promise<int> p;
    std::future result = p.get_future();
    std::thread t(&Server::Open, server, &p);

    curText = &waitforUserText;
    textArraySize = 1;
    ShowTitlePanel();

    t.join();

    if(result.get() == 1) {
        curText = &matchingText;
        textArraySize = 1;
        gameScene->InitServer(server);
        ShowTitlePanel();
        isConnection = true;
    }
    else {
        curText = &failToCreateRoom;
        ShowTitlePanel();
    }
}

void TitleScene::JoinRoom()
{
    client = new Client(port);
    std::promise<int> p;
    std::future<int> result = p.get_future();
    std::thread t(&Client::Connected, client, std::move(p));

    curText = &duringMatcing;
    textArraySize = 1;F
    ShowTitlePanel();
    t.join();
    
    if(result.get() == 1) {
        curText = &matchingText;
        textArraySize = 1;
        
        gameScene->InitClient(client);
        ShowTitlePanel();
        isConnection = true;
    }  
    else {
        curText = createorjoinText;
        textArraySize = 2;
        ShowTitlePanel();
    }
}
