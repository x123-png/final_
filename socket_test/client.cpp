#include <bits/stdc++.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <ws2tcpip.h>
using namespace std;

int main(){
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);

    SOCKET client_socket=socket(AF_INET,SOCK_STREAM,0);
    if(client_socket==INVALID_SOCKET){
        cerr<<"socket创建失败"<<endl;
        return -1;
    }

    struct sockaddr_in target;
    target.sin_family=AF_INET;
    target.sin_port=htons(9999);
    target.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(connect(client_socket,(struct sockaddr*)&target,sizeof target)==INVALID_SOCKET){
        cerr<<"connect error"<<endl;
        closesocket(client_socket);
        return -1;
    }

    char buffer[1024]={""};
    for(int i=0;i<784;i++){
        buffer[i]='1';
    }

    for(int i=0;i<sizeof(buffer);i++){
        cout<<buffer[i]<<" ";
    }
    send(client_socket,buffer,sizeof buffer,0);

    char buffer2[1024]={""};
    int ret=recv(client_socket,buffer2,sizeof buffer2,0);
    if(ret<0){
        cout<<"server disconnect"<<endl;
    }
    cout<<buffer2<<endl;
    closesocket(client_socket);
    return 0;
}