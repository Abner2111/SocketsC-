#include "SocketClient.h"

SocketClient::SocketClient() {}

void SocketClient::set_connection() {
    //Create a descriptor
    descriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//IPV4
    if(descriptor<0)
        cout<<"Error al crear el socket"<<endl;
    info.sin_family = AF_INET;
    info.sin_addr.s_addr = inet_addr("127.0.0.1");
    info.sin_port=ntohs(4050);//htons translates bytes to ints understandable ny ipv4
    memset(&info.sin_zero, 0, sizeof(info.sin_zero)); //cleans the structure

    if((connect(descriptor,(sockaddr *)&info, (socklen_t)sizeof(info)))<0){
        cout<<"There was an error while connecting to the server"<<endl;
    }

    cout<<"Client-server connection established"<<endl;

    pthread_t thd;

    pthread_create(&thd, 0, SocketClient::Controller, (void *)this);
    pthread_detach(thd);
}

void * SocketClient::Controller(void *obj) {
    SocketClient* c=(SocketClient *)obj;
    while(true){
        string message;
        char buffer[1024] = {0};
        while(true){
            memset(buffer, 0, 1024);
            int bytes = recv(c->descriptor, buffer, 1024, 0);
            message.append(buffer, bytes);
            if(bytes <=0){
                close(c->descriptor);
                pthread_exit(NULL);
            }
            if(bytes < 1024){
                break;
            }
        }
        cout << message << endl;
    }
    close(c->descriptor);
    pthread_exit(NULL);
}

void SocketClient::setMessage(const char *msn) {
    send(descriptor, msn, strlen(msn),0);
}
