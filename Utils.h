 
#ifndef UTILS_H
#define UTILS_H

#include "stdafx.h"
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <string>

class Utils {
private:

public:
    static void ClearScreen()
    {
        std::cout << "\033[2J\033[H" << std::flush;
    }

    static struct winsize GetTerminalSize(){
        static struct winsize ws;
        if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1) {
            return ws;
        }
        return ws;
    }

    // stdin을 논블로킹 모드로 설정
    static void SetNonBlocking(bool enable) {
        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        if (enable)
            fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
        else
            fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
    }

    static std::vector<std::string> SplitString(std::string str,const char splitword){

        int pointer = 0;
        int prevPointer = 0;
        std::vector<std::string> temp;
        while(str.size() > pointer) {
            if(str[pointer] == splitword) {
                temp.push_back(str.substr(prevPointer, pointer - prevPointer));
                std::cout << str.substr(prevPointer, pointer - prevPointer) << std::endl;
                prevPointer = pointer + 1;
            }
            pointer++;
        }

        if(prevPointer != pointer) {
            if(str.substr(prevPointer, pointer- prevPointer).size() != 0 && str.substr(prevPointer, pointer- prevPointer) != " ") {
                temp.push_back(str.substr(prevPointer, pointer - prevPointer));
                std::cout << str.substr(prevPointer, pointer - prevPointer) << std::endl;
            }
        }

        return temp;
    }
};

#endif // UTILS_H