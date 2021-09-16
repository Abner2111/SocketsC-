//
// Created by abner on 12/9/21.
//

#ifndef UNTITLED3_SOCKETCLIENT_H
#define UNTITLED3_SOCKETCLIENT_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

class SocketClient{
public:
    SocketClient();
    void set_connection();
    void setMessage(const char* msn);
private:
    int descriptor; // identifies the system
    sockaddr_in info; //socket info

    static void* Controller(void* obj);

};


#endif //UNTITLED3_SOCKETCLIENT_H
