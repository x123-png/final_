#include "part1.h"
#include <iostream>
using namespace std;

int main(){
    //构造model类对象，四个矩阵均为空
    vector<vector<float>> w1(784,vector<float>(500,0));
    vector<vector<float>> b1(1,vector<float>(500,0));
    vector<vector<float>> w2(500,vector<float>(10,0));
    vector<vector<float>> b2(1,vector<float>(10,0));
    model mod(w1,b1,w2,b2);

    vector<vector<float>> xtmp(1,vector<float>(784,0));
    for(int i=0;i<784;i++){
        cin>>xtmp[0][i];
    }

    matrix x(xtmp);
    matrix tmpMatr(x.multiplyMatrix(mod.m_w1));  //x*w1
    matrix tmp1Matr(mod.RELU(tmpMatr.addMatrix(mod.m_b1)));//完成relu(x * w1 + b1)操作
    matrix tmp2Matr(tmp1Matr.multiplyMatrix(mod.m_w2));  //relu(x * w1 + b1) * w2
    auto r=mod.SoftMax(tmp2Matr.addMatrix(mod.m_b2));  //完成softmax(relu(x * w1 + b1) * w2 + b2),r是公式计算结果向量
    
}