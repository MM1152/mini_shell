#include "../stdafx.h"
#include "TitleScene.h"
#include "../Define.h"

class MainGame {
private:
    TitleScene* titleScene;    

    struct winsize ws;
    int width = 0;
    int height = 0;
    char input;

public:
    void Play();
    struct winsize* GetTerminalSize();
};