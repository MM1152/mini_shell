#include "stdafx.h"

class Utils {
public:
    static void ClearScreen()
    {
        std::cout << "\033[2J\033[H" << std::flush;
    }
};