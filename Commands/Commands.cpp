#include "Commands.h"

Commands::Commands()
{
    commands.insert({"cd", [this](char** args) { ExecuteCd(args); }});
    commands.insert({"exit", [this](char** args) { ExecuteExit(args); }});
    commands.insert({">", [this](char** args) { Redirections(args); }});
    commands.insert({">>", [this](char** args) { Redirections(args); }});
    commands.insert({"<", [this](char** args) { Redirections(args); }});
    commands.insert({"|", [this](char** args) { Pipe(args); }});
    commands.insert({"game", [this](char** args) { Game(args); }});
}

void Commands::Execute(char **args)
{
    for(int i = 0; args[i] != NULL; i++) {
        if(commands.find(args[i]) != commands.end()) {
            commands[args[i]](args);
            return;
        }
    }
    ExecuteInitialLinuxCommand(args);
}

void Commands::ExecuteCd(char **args)
{
    if(chdir(args[1]) != 0) {
        perror("Fail to change directory");
    }
}

void Commands::ExecuteExit(char **args)
{
    exit(0);
}

void Commands::ExecuteInitialLinuxCommand(char **args)
{
    if(fork() == 0) {
        execvp(args[0], args);
        perror("Fail to excute args");
        exit(1);
    }
    else {
        wait(NULL);
    }
}

void Commands::Redirections(char **args)
{
    int redirectionIndex = 0;
    while(args[redirectionIndex] != NULL) {
        if(strcmp(args[redirectionIndex], ">") == 0){
            args[redirectionIndex] = NULL;
            Out_Redirection(args, redirectionIndex);
            break;
        }
        else if(strcmp(args[redirectionIndex], ">>") == 0){
            args[redirectionIndex] = NULL;
            Append_Redirection(args, redirectionIndex);
            break;
        }
        else if(strcmp(args[redirectionIndex], "<") == 0){
            args[redirectionIndex] = NULL;
            In_Redirection(args, redirectionIndex);
            break;
        }

        redirectionIndex++;
    }
}

void Commands::Out_Redirection(char **args, int index)
{
    // 입력을 변경시켜야됨
    // 왼쪽의 출력을 오른쪽 파일에 저장하는 형식
    // 기존 출력은 터미널에 뛰어져야 하지만 dup2 를 통해서 출력을 파일로 변경시켜야됌
    if(fork() == 0) {
        int fd = open(args[index + 1], O_WRONLY | O_CREAT | O_TRUNC , 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);

        execvp(args[0], args);
    }
    else {
        wait(NULL);
    }
}

void Commands::Append_Redirection(char **args, int index)
{
    if(fork() == 0) {
        int fd = open(args[index + 1], O_WRONLY | O_APPEND | O_CREAT , 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);

        execvp(args[0], args);
    }
    else {
        wait(NULL);
    }
}

void Commands::In_Redirection(char **args, int index)
{
    if(fork() == 0) {
        int fd = open(args[index + 1], O_RDONLY);
        dup2(fd, STDIN_FILENO);
        close(fd);

        execvp(args[0], args);
    }
    else {
        wait(NULL);
    }
}

void Commands::Pipe(char **args)
{
    int pipeIndex = 0;
    while(args[pipeIndex] != NULL) {
        if(strcmp(args[pipeIndex], "|") == 0) {
            args[pipeIndex] = NULL;
            break;
        }
        pipeIndex++;
    }

    int fd[2];
    if(pipe(fd) != -1) {
        if(fork() == 0) {
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            close(fd[0]);
            execvp(args[0], args);
            exit(0);
        }
        else if(fork() == 0) {
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);
            execvp(args[pipeIndex + 1], &args[pipeIndex + 1]);
            exit(0);
        }
        else {
            close(fd[0]);
            close(fd[1]);
            wait(NULL);
            wait(NULL);
        }
    }

    
}

void Commands::Game(char **args)
{
    if(fork() == 0){
        mainGame.Play();
    }
    else {
        wait(NULL);
    }
}
