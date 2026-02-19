#include "Define.h"
#include "Commands/Commands.h"
#include "stdafx.h"

using namespace std;

class Shell {
private:
    Commands commands;

public:
    char* args[Define::MAX_ARGS];
    char input[Define::MAX_INPUT];    
    char cwd[Define::MAX_CWD];
    
    ~Shell() = default;
    void SplitWord(char* input, char** args);
    void ExecuteCommand(char** args);
};