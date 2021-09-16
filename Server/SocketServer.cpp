
#include "SocketServer.h"

SocketServer::SocketServer() {}

bool SocketServer::create_socket() {
    //Create a descriptor
    descriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//IPV4
    if(descriptor<0)
        return false;
    info.sin_family = AF_INET;
    info.sin_addr.s_addr = INADDR_ANY;
    info.sin_port=htons(4050);//htons translates int to bytes understandable ny ipv4
    memset(&info.sin_zero, 0, sizeof(info.sin_zero)); //cleans the structure
    return true;
}

bool SocketServer::bind_kernel() {
    if((bind(descriptor,(sockaddr *)&info, (socklen_t)sizeof(info)))<0)
        return false;
    //listen for clients
    listen(descriptor, 4); //seccond attribute sets the maximun client amount
    return true;
}

void SocketServer::run(){
    if(!create_socket())
        throw string("there was an error while creating the socket");
    if(!bind_kernel())
        throw string("there was an error while binding the kernel");
    //Endless cycle for accepting clients
    while(true){
        dataSocket data;
        socklen_t t = sizeof(data.info);
        cout << "Waiting for client connection.."<<endl;
        data.descriptor = accept(descriptor, (sockaddr *)&data.info, &t);
        if(data.descriptor < 0){
            cout<<"Error al aceptar el cliente"<<endl;
            break;
        } else {
            clients.push_back(data.descriptor);
            cout << "Cliente conectado"<<endl;
            pthread_t thread;
            pthread_create(&thread, nullptr, SocketServer::ClientController, (void*)&data);
            pthread_detach(thread);
        }
    }
    close(descriptor);
}

void * SocketServer::ClientController(void *obj) {
    dataSocket* data = (dataSocket *)obj;
    while(true){
        string message;
        char buffer[1024] = {0};
        while(true){
            memset(buffer, 0, 1024);
            int bytes = recv(data->descriptor, buffer, 1024, 0);
            message.append(buffer, bytes);
            if(bytes <=0){
                close(data->descriptor);
                pthread_exit(NULL);
            }
            if(bytes < 1024){
                break;
            }
        }
        cout << message << endl;
    }
    close(data->descriptor);
    pthread_exit(NULL);
}

void SocketServer::setMessage(const char *msn) {
    for(int i=0; i<clients.size();i++){
        send(clients[i], msn, strlen(msn),0);

    }
}