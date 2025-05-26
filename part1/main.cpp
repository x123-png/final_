#include "part1.h"
#include <fstream>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <chrono>
using namespace std;
using json = nlohmann::json;

//r是行（row），c是列（column）

template<typename T>
void read_file(ifstream& file,vector<vector<T>>& v,int l,int r);

template<typename T>
model<T>* modelptr(ifstream&,vector<vector<T>>&,int,int,ifstream&,vector<vector<T>>&,int,int,ifstream&,vector<vector<T>>&,int,int,ifstream&,vector<vector<T>>&,int,int,model<T>*&);

int main(){
    //读取二进制文件中的矩阵信息
    //读取矩阵大小
    string type;
    vector<vector<int>> j_value(4,vector<int>(2,0));
    ifstream j_file("D:\\GKD_final_test\\GKD-Software-2025-Test-main\\mnist-fc-plus\\meta.json");
    if(!j_file.is_open()){
        cerr<<"json文件读取失败:"<<endl;
        j_file.close();
        return 1;
    }
    json j;
    j_file>>j;
    type=j["type"];
    j_value[0][0]=j["fc1.weight"][0];
    j_value[0][1]=j["fc1.weight"][1];
    j_value[1][0]=j["fc1.bias"][0];
    j_value[1][1]=j["fc1.bias"][1];
    j_value[2][0]=j["fc2.weight"][0];
    j_value[2][1]=j["fc2.weight"][1];
    j_value[3][0]=j["fc2.bias"][0];
    j_value[3][1]=j["fc2.bias"][1];
    //读取文件
    
    //w1 784*500
    ifstream ifsw1;
    ifsw1.open("D:/GKD_final_test/GKD-Software-2025-Test-main/mnist-fc-plus/fc1.weight",ios::in|ios::binary);
    if(ifsw1.is_open()==false){
        cerr<<"fc1.weight文件打开失败:";
        ifsw1.close();
        return -1;
    }
    //b1 1*500
    ifstream ifsb1;
    ifsb1.open("D:/GKD_final_test/GKD-Software-2025-Test-main/mnist-fc-plus/fc1.bias",ios::in|ios::binary);
    if(ifsb1.is_open()==false){
        cerr<<"fc1.bias文件打开失败:";
        ifsb1.close();
        return -2;
    }
    //w2 500*10
    ifstream ifsw2;
    ifsw2.open("D:/GKD_final_test/GKD-Software-2025-Test-main/mnist-fc-plus/fc2.weight",ios::in|ios::binary);
    if(ifsw2.is_open()==false){
        cerr<<"fc2.weight文件打开失败:";
        ifsw2.close();
        return -3;
    }    
    //b2 1*10
    ifstream ifsb2;
    ifsb2.open("D:/GKD_final_test/GKD-Software-2025-Test-main/mnist-fc-plus/fc2.bias",ios::in|ios::binary);
    if(ifsb2.is_open()==false){
        cerr<<"fc1.bias文件打开失败:";
        ifsb2.close();
        return -4;
    }

    if(type=="fp32"){        
        vector<vector<float>> w1r(j_value[0][0],vector<float>(j_value[0][1],0));
        vector<vector<float>> b1r(j_value[1][0],vector<float>(j_value[1][1],0));
        vector<vector<float>> w2r(j_value[2][0],vector<float>(j_value[2][1],0));
        vector<vector<float>> b2r(j_value[3][0],vector<float>(j_value[3][1],0));
        model_float A(w1r,b1r,w2r,b2r);
        model<float>* mod=&A;  //抽象类不能直接创建需要通过派生类构造
        mod=modelptr(ifsw1,w1r,j_value[0][0],j_value[0][1],ifsb1,b1r,j_value[1][0],j_value[1][1],ifsw2,w2r,j_value[2][0],j_value[2][1],ifsb2,b2r,j_value[3][0],j_value[3][1],mod);
        
        vector<vector<float>> xtmp(1,vector<float>(784,1.0f));
        matrix x(xtmp);
        auto start=chrono::high_resolution_clock::now();  //开始记录时间
        auto r=mod->foward(x,*mod);
        auto stop=chrono::high_resolution_clock::now();//程序运行结束时间
        auto time=chrono::duration_cast<chrono::milliseconds>(stop-start);
        cout<<"time:"<<time<<"/n"<<endl;   //初始时间

        for(int i=0;i<10;i++){
            cout<<r[0][i]<<" ";
        }
    }
    else if(type=="fp64"){
        vector<vector<double>> w1r(j_value[0][0],vector<double>(j_value[0][1],0));
        vector<vector<double>> b1r(j_value[1][0],vector<double>(j_value[1][1],0));
        vector<vector<double>> w2r(j_value[2][0],vector<double>(j_value[2][1],0));
        vector<vector<double>> b2r(j_value[3][0],vector<double>(j_value[3][1],0));
        model_double B(w1r,b1r,w2r,b2r);
        model<double>* mod=&B;  
        mod=modelptr(ifsw1,w1r,j_value[0][0],j_value[0][1],ifsb1,b1r,j_value[1][0],j_value[1][1],ifsw2,w2r,j_value[2][0],j_value[2][1],ifsb2,b2r,j_value[3][0],j_value[3][1],mod);
        
        vector<vector<double>> xtmp(1,vector<double>(784,1.0f));
        matrix x(xtmp);
        auto start=chrono::high_resolution_clock::now();  //开始记录时间
        auto r=mod->foward(x,*mod);
        auto stop=chrono::high_resolution_clock::now();//程序运行结束时间
        auto time=chrono::duration_cast<chrono::milliseconds>(stop-start);
        cout<<"time:"<<time<<"/n"<<endl;   //初始时间10ms,6ms

        for(int i=0;i<10;i++){
            cout<<r[0][i]<<" ";
        }
    }
    
    ifsw1.close();
    ifsb1.close();
    ifsw2.close();
    ifsb2.close();
    j_file.close();
    return 0;
}

template<typename T>
void read_file(ifstream& file,vector<vector<T>>& v,int l,int R){
    for(int i=0;i<l;i++){
        for(int r=0;r<R;r++){
            T tmp;
            file.read((char*)&tmp,sizeof(T));
            v[i][r]=tmp;
        }
    }
};
  //读入文件且返回model基类指针
template<typename T>
model<T>* modelptr(ifstream& ifsw1,vector<vector<T>>& w1r,int l_w1,int R_w1,ifstream& ifsb1,vector<vector<T>>& b1r,
    int l_b1,int R_b1,ifstream& ifsw2,vector<vector<T>>& w2r,int l_w2,int R_w2,ifstream& ifsb2,vector<vector<T>>& b2r,
    int l_b2,int R_b2,model<T>*& p){
        read_file(ifsw1,w1r,l_w1,R_w1);
        read_file(ifsb1,b1r,l_b1,R_b1);
        read_file(ifsw2,w2r,l_w2,R_w2);
        read_file(ifsb2,b2r,l_b2,R_b2);
        p->m_w1=w1r;
        p->m_b1=b1r;
        p->m_w2=w2r;
        p->m_b2=b2r;
        return p;
}