#include "MainGame.h"

void MainGame::Play()
{
    titleScene = new TitleScene();

    while(1) {
        if(GetTerminalSize() == nullptr) {
            std::cout << "error to get terminal size" << std::endl;            
        }
        ws = *(GetTerminalSize());
        width = ws.ws_col;
        height = ws.ws_row;
        
        titleScene->ShowTitlePanel();

        std::cin.clear();
        std::cin >> input;

        if(titleScene->ChangeText(input) == -1) {
            break;
        }
    }

    delete titleScene;
}

winsize* MainGame::GetTerminalSize()
{
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1) {
        return &ws;
    }

    return nullptr;
}
