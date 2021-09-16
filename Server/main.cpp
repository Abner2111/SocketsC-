#include "SocketServer.h"
#include "json.hpp"

using json = nlohmann::json;
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
    json json_message;

    string name;
    string age;
    string gender;
    while(true){
        cout << "Name:"<<endl;
        cin >> name;
        json_message["name"] = name;
        cout << "Age:"<<endl;
        cin >> age;
        json_message["age"] =age;
        cout << "Gender"<<endl;
        cin >> gender;
        json_message["gender"] = gender;

        std::string msg = json_message.dump();
        if (name=="exit" || age =="exit"||gender=="exit")
            break;
        server->setMessage(msg.c_str());
    }

    return 0;
}
