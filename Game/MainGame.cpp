#include "MainGame.h"
#include "GameScene.h"
#include "TitleScene.h"

void MainGame::Play()
{
    GameScene* gameScene = new GameScene();
    titleScene = new TitleScene(gameScene);
    
    while(1) {
        struct winsize ws = Utils::GetTerminalSize();
        width = ws.ws_col;
        height = ws.ws_row;
        
        if(!titleScene->isConnection) {
            titleScene->ShowTitlePanel();

            std::cin.clear();
            std::cin >> input;

            if(titleScene->ChangeText(input) == -1) {
                break;
            }
        }
        else {
           break;
        }
    }
    gameScene->DrawMap();
    delete titleScene;
}
