#include "Client.h"
#include "../Define.h"
#include <future>

void Client::ReConnected()
{
    if(connect(sock, (sockaddr*) socketAddress, sizeof(sockaddr_in)) < 0){
        std::cout << "다시 찾는 중.. " << std::endl;
        return;
    }    
    connection = true;
}

Client::Client(int port)
{
    socketAddress = new sockaddr_in();
    sock = socket(AF_INET, SOCK_STREAM, 0);

    socketAddress->sin_family = AF_INET;
    socketAddress->sin_port = htons(port);
    socketAddress->sin_addr.s_addr = inet_addr("127.0.0.1");
}

Client::~Client()
{
    close(sock);
}


void Client::Connected(std::promise<int> p)
{
    connection = false;
    int connectCount = 0;

    while(connectCount < Define::RECONNECT_COUNT) {
        std::thread t(&Client::ReConnected, this);
        std::this_thread::sleep_for(std::chrono::seconds(3));

        if(connection) {
            t.join();
            break;
        }

        close(sock);
        t.join();
        connectCount++;
        sock = socket(AF_INET, SOCK_STREAM, 0);
    }

    if(connection) 
        p.set_value(1);
    else {
        p.set_value(-1);
    }
}