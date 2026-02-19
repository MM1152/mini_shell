#include <map>
#include <string>
#include <functional>
#include "../stdafx.h"
#include "../Game/MainGame.h"

class Commands {
public:
    Commands();
    void Execute(char** args);
    void ExecuteCd(char** args);
    void ExecuteExit(char** args);
    void ExecuteInitialLinuxCommand(char** args);

    void Redirections(char** args);
    void Out_Redirection(char** args, int index);
    void Append_Redirection(char** args, int index);
    void In_Redirection(char** args, int index);

    void Pipe(char** args);

    void Game(char** args);
private:
    MainGame mainGame;
    std::map<std::string, std::function<void(char**)>> commands;
};

