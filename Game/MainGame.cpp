#include "MainGame.h"
#include "GameScene.h"

void MainGame::Play()
{
    GameScene* gameScene = new GameScene();
    titleScene = new TitleScene(gameScene);
    
    while(1) {
        if(GetTerminalSize() == nullptr) {
            std::cout << "error to get terminal size" << std::endl;            
        }
        ws = *(GetTerminalSize());
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

winsize* MainGame::GetTerminalSize()
{
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1) {
        return &ws;
    }

    return nullptr;
}
