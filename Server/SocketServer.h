//
// Created by abner on 30/8/21.
//

#ifndef SERVER_SOCKETSERVER_H
#define SERVER_SOCKETSERVER_H


#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>
using namespace std;
//Structure to represent the clients
struct dataSocket{
    int descriptor;
    sockaddr_in info;

};
class SocketServer{
public:
    SocketServer();
    void run();
    void setMessage(const char* msn);
private:
    int descriptor; // identifies the system
    sockaddr_in info; //Server socket info
    vector<int> clients; //Stores the connected clients

    bool create_socket();
    bool bind_kernel();
    static void* ClientController(void* obj); //void* obj accepts all types of object

};


#endif //SERVER_SOCKETSERVER_H
