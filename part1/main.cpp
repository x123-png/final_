#include "part1.h"
//#include "json/include/json/json.h"
#include <fstream>
#include <iostream>
using namespace std;

int main(){
    //读取二进制文件中的矩阵信息
    //w1 784*500
    ifstream ifsw1;
    ifsw1.open("D:/GKD_final_test/GKD-Software-2025-Test-main/mnist-fc/fc1.weight",ios::in|ios::binary);
    if(ifsw1.is_open()==false){
        cerr<<"fc1.weight文件打开失败:";
        ifsw1.close();
        return -1;
    }
    vector<vector<float>> w1r(784,vector<float>(500,0));
    for(int l=0;l<784;l++){
        for(int r=0;r<500;r++){
            float tmp;
            ifsw1.read((char*)&tmp,sizeof(float));
            w1r[l][r]=tmp;
        }
    }    
    
    //b1 1*500
    ifstream ifsb1;
    ifsb1.open("D:/GKD_final_test/GKD-Software-2025-Test-main/mnist-fc/fc1.bias",ios::in|ios::binary);
    if(ifsb1.is_open()==false){
        cerr<<"fc1.bias文件打开失败:";
        ifsb1.close();
        return -2;
    }
    vector<vector<float>> b1r(1,vector<float>(500,0));
    for(int r=0;r<500;r++){
        float tmp;
        ifsb1.read((char*)&tmp,sizeof(float));
        b1r[0][r]=tmp;
        //cout<<b1r[0][r]<<" "; //读取正常
    }
    
    //w2 500*10
    ifstream ifsw2;
    ifsw2.open("D:/GKD_final_test/GKD-Software-2025-Test-main/mnist-fc/fc2.weight",ios::in|ios::binary);
    if(ifsw2.is_open()==false){
        cerr<<"fc2.weight文件打开失败:";
        ifsw2.close();
        return -3;
    }
    vector<vector<float>> w2r(500,vector<float>(10,0));
    for(int l=0;l<500;l++){
        for(int r=0;r<10;r++){
            float tmp;
            ifsw2.read((char*)&tmp,sizeof(float));
            w2r[l][r]=tmp;
        }
    }    
    
    //b2 1*10
    ifstream ifsb2;
    ifsb2.open("D:/GKD_final_test/GKD-Software-2025-Test-main/mnist-fc/fc2.bias",ios::in|ios::binary);
    if(ifsb2.is_open()==false){
        cerr<<"fc1.bias文件打开失败:";
        ifsb2.close();
        return -2;
    }
    vector<vector<float>> b2r(1,vector<float>(10,0));
    for(int r=0;r<10;r++){
        float tmp;
        ifsb2.read((char*)&tmp,sizeof(float));
        b2r[0][r]=tmp;
    }
    
    //构造model类对象，四个矩阵均为空
    // vector<vector<float>> w1(784,vector<float>(500,0));
    // vector<vector<float>> b1(1,vector<float>(500,0));
    // vector<vector<float>> w2(500,vector<float>(10,0));
    // vector<vector<float>> b2(1,vector<float>(10,0));
    model mod(w1r,b1r,w2r,b2r);

    vector<vector<float>> xtmp(1,vector<float>(784,2.0));

    matrix x(xtmp);
    auto r=mod.foward(x,mod);
    for(int i=0;i<10;i++){
        cout<<r[0][i]<<" ";
    }
    
    ifsw1.close();
    ifsb1.close();
    ifsw2.close();
    ifsb2.close();
}