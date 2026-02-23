// ...existing code...
#ifndef MAINGAME_H
#define MAINGAME_H

#include "../stdafx.h"
#include "../Define.h"

class TitleScene;

class MainGame {
private:
    TitleScene* titleScene;
    int width = 0;
    int height = 0;
    char input;
public:
    void Play();
};

#endif // MAINGAME_H