#include "../stdafx.h"
#include "../Utils.h"
#include "Server.h"
#include "Client.h"

class TitleScene{
private:
    Server* server;
    Client* client;

    const std::string titleText = "오목 게임";
    const std::string selectText[2] = {
        "1. 게임 시작",
        "2. 종료",
    };
    const std::string createorjoinText[2] = {
        "1. 방 입장",
        "2. 방 만들기"
    };
    const std::string waitforUserText = "유저 접속 기다리는 중";
    const std::string waitforJoinRoom = "방 찾는 중";
    const std::string matchingText = "매칭 되었습니다.";
    const std::string duringMatcing = "매칭 중입니다.";
    
    const std::string* curText;
    int textArraySize;

public:
    TitleScene();
    ~TitleScene();
    int ChangeText(int input);
    void ShowTitlePanel();
    void CreateRoom();
    void JoinRoom();
};