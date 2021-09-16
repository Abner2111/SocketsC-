#include "SocketClient.h"
#include "json.hpp"
SocketClient* client;

void * clientRun(void *){
    try {
        client->set_connection();
    } catch (string ex){
        cout<<ex<<endl;
    }
    pthread_exit(NULL);
}
int main() {
    client  = new SocketClient;
    pthread_t thd;
    pthread_create(&thd, 0, clientRun, NULL);
    pthread_detach(thd);

    string json = "Hola desde el cliente";

    while(true){
        string msn;
        cin>>msn;
        if(msn =="salir")
            break;
        client->setMessage(msn.c_str());
    }

    delete client;
    return 0;
}
