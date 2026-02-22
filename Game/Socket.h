#include "../stdafx.h"

class Socket {
    public:
        bool Send(const std::string& data);
        std::string Receive();
};