#include "stdafx.h"
#include "Shell.h"
#include "Define.h"

int main(){
    Shell shell;

    while(1) {
        if(getcwd(shell.cwd, Define::MAX_CWD) != NULL) {
            std::cout << shell.cwd << " $ ";
        }

        if(fgets(shell.input, Define::MAX_INPUT, stdin) != NULL) {
            shell.input[strcspn(shell.input, "\n")] = 0;            
        }
        else {
            continue;
        }

        shell.SplitWord(shell.input, shell.args);
        shell.ExecuteCommand(shell.args);
    }

    return 0;
}