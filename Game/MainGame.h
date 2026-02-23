// ...existing code...
#ifndef MAINGAME_H
#define MAINGAME_H

#include "../stdafx.h"
#include "../Define.h"
#include <future>

class TitleScene;
class GameScene;

class MainGame {
private:
    TitleScene* titleScene;
    GameScene* gameScene;
    int width = 0;
    int height = 0;
    std::string input;
public:
    ~MainGame();
    void Play();
    void Release();
    void InputThread(std::promise<char>* p, std::promise<bool>* p1);
};

#endif // MAINGAME_H