#include <bits/stdc++.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

vector<vector<double>> creatmatrix(char []);

int main(){
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,2),&WSAData);

    SOCKET listen_socket=socket(AF_INET,SOCK_STREAM,0);
    if(listen_socket==INVALID_SOCKET){
        cerr<<"socket创建失败"<<endl;
        return -1;
    }

    struct sockaddr_in local={0};
    local.sin_family = AF_INET;
    local.sin_addr.s_addr=INADDR_ANY;
    local.sin_port=htons(9999);
    if(bind(listen_socket,(struct sockaddr*)&local,sizeof(local))==INVALID_SOCKET){
        cerr<<"bind error"<<endl;
        return -1;
    }
    if(listen(listen_socket,128)==SOCKET_ERROR){
        cerr<<"listen error"<<endl;
        return -1;
    }

    SOCKET client_socket=accept(listen_socket,nullptr,nullptr);
    cout<<"client connect:"<<client_socket<<endl;

    char buffer[1024]={""};
    int ret=recv(client_socket,buffer,sizeof buffer,0);  //接收信息
    if(ret<=0){
        cout<<"client disconnect:"<<client_socket<<endl;
        return -1;
    }

    vector<vector<double>> v=creatmatrix(buffer); 
    for(int l=0;l<v.size();l++){
        for(int r=0;r<v[0].size();r++){
            cout<<v[l][r]<<" ";
        }
        cout<<endl;
    }

    for(int i=0;i<(v.size())*(v[0].size());i++){
        buffer[i]=v[0][i];
    }
    send(client_socket,buffer,strlen(buffer),0);
    closesocket(client_socket);
    closesocket(listen_socket);
    WSACleanup();
    return 0;
}

vector<vector<double>> creatmatrix(char buffer[]){
    vector<vector<double>> v(1,vector<double>(784,0));
    for(int i=0;i<sizeof(buffer);i++){
        v[0][i]=buffer[i];
    }
    return v;
}