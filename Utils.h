 
#ifndef UTILS_H
#define UTILS_H

#include "stdafx.h"

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
};

#endif // UTILS_H