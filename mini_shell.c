#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64
#define MAX_CWD 1024

int main(){
    char input[MAX_INPUT];
    char* args[MAX_ARGS];
    char cwd[MAX_CWD];

    while(1) {
        if(getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s> ", cwd);
        }
        fflush(stdout);

        if(fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        input[strcspn(input, "\n")] = 0;
        
        if(strcmp(input, "exit") == 0) {
            break;
        }

        int i = 0;
        char* token = strtok(input, " ");
        while(token != NULL && i < MAX_ARGS - 1){
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if(strcmp(args[0], "cd") == 0) {
            chdir(args[1]);
            continue;
        }

        pid_t pid = fork();
        if(pid == 0) {
            execvp(args[0] , args);
            perror("Fail to excute args");
            exit(1);
        }
        else {
            wait(NULL);
        }
    }

    return 0;
}