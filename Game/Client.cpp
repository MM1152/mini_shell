#include "Client.h"
#include "../Define.h"
#include <future>
void Client::ReConnected()
{
    if(connect(sock, (sockaddr*)&server, sizeof(server)) < 0){
        std::cout << "다시 찾는 중.. " << std::endl;
        return;
    }    
    connection = true;
}

Client::Client()
{
    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(7777);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
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

void Client::SendData()
{
    char msg[1024];
    while(1) {
        std::cin >> msg;
        if(send(sock, msg, sizeof(msg), 0) <= 0) {
            break;
        }
    }
}

void Client::RecvData()
{
    while(1) {
        if(recv(sock, buffer, sizeof(buffer), 0) <= 0) {
            break;
        } 
        std::cout << "Server Send : " << buffer << std::endl;       
    }
}
