#include "SocketServer.h"
#include "json.hpp"
SocketServer* server;
void * serverRun(void *){
    try{
        server->run();
    } catch (string ex){
        cout << ex << endl;
    }
    pthread_exit(NULL);
}

int main() {
    server = new SocketServer;
    pthread_t serverTherad;
    pthread_create(&serverTherad, 0, serverRun, NULL);
    pthread_detach(serverTherad);

    //Cycle to send messages to the client
    string json = "Hola desde el servidor";
    while(true){
        string msn;
        cin >> msn;
        if(msn == "salir")
            break;
        server->setMessage(msn.c_str());
    }
    return 0;
}
