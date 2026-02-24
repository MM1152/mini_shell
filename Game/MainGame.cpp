#include <atomic>
#include <thread>

#include "MainGame.h"
#include "GameScene.h"
#include "TitleScene.h"
#include <csignal>
#include <atomic>
#include <thread>
#include <string>
MainGame::~MainGame()
{
    delete gameScene;
    delete titleScene;
    std::cout << "종료" << std::endl;
    exit(1);
}

void MainGame::Play()
{
    gameScene = new GameScene();    
    titleScene = new TitleScene(gameScene);

    while(1) {
        struct winsize ws = Utils::GetTerminalSize();
        width = ws.ws_col;
        height = ws.ws_row;

        if(!titleScene->isConnection) {
            titleScene->ShowTitlePanel();

            std::getline(std::cin, input);

            if(titleScene->ChangeText(input) == -1) {
                break;
            }
        }
        else {
            std::cout << "Draw map" << std::endl;
            gameScene->DrawMap();
            break;
        }
    }
}
