#include "Shell.h"

void Shell::ExecuteCommand(char** args)
{
    commands.Execute(args);
}

void Shell::SplitWord(char* input, char** args)
{
    int i = 0;
    char* token;
    
    while((token = strtok(input, " ")) != NULL && i < Define::MAX_ARGS - 1) {
        args[i++] = token;
        input = NULL;
    }
    args[i] = NULL;
}
