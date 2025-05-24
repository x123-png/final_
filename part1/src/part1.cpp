#include "part1.h"
#include <iostream>
#include <cmath>

template<class T>
std::vector<std::vector<T>> matrix<T>::getMatrix(){
    return localMatrix;
}

template<class T>
std::vector<std::vector<T>> matrix<T>::addMatrix(std::vector<std::vector<T>> matr){
    for(int l=0;l<line;l++){
        for(int r=0;r<row;r++){
            localMatrix[l][r]+=matr[l][r];
        }
    }
    return localMatrix;
}

template<class T>
int matrix<T>::getLine(){
    return line;
}

template<class T>
int matrix<T>::getRow(){
    return row;
}

template<class T>
std::vector<std::vector<T>> matrix<T>::multiplyMatrix(std::vector<std::vector<T>> const matr){
    std::vector<std::vector<T>> result(line,std::vector<T>(matr[0].size(),0.0f));
    for(int l=0;l<line;l++){  //结果的行
        for(int r=0;r<matr[0].size();r++){  
            for(int i=0;i<row;i++){
                result[l][r]+=localMatrix[l][i]*matr[i][r];
            }
        }        
    }
    return result;
}

template<class T>
std::vector<std::vector<T>> model<T>::RELU(std::vector<std::vector<T>> m){
    for(int l=0;l<m.size();l++){
        for(int r=0;r<m[0].size();r++){
            if(m[l][r]<0) m[l][r]=0;
        }
    }
    return m;
}

template<class T>
std::vector<std::vector<T>> model<T>::SoftMax(std::vector<std::vector<T>> v){
    double e=exp(1);   //e是e^1
    std::vector<std::vector<T>> soft(1,std::vector<T>(10,0.0f));
    float deno=0;  //分母
    for(int i=0;i<v[0].size();i++){
        deno+=std::pow(e,v[0][i]);
    }
    for(int i=0;i<v.size();i++){
        soft[0][i]=std::pow(e,v[0][i])/deno;
    }
    return soft;
}

std::vector<std::vector<float>> model_float::foward(matrix<float>& x,model<float>& mod){    
    matrix tmpMatr(x.multiplyMatrix(mod.m_w1));  //x*w1
    matrix tmp1Matr(mod.RELU(tmpMatr.addMatrix(mod.m_b1)));//完成relu(x * w1 + b1)操作
    matrix tmp2Matr(tmp1Matr.multiplyMatrix(mod.m_w2));  //relu(x * w1 + b1) * w2
    auto r=mod.SoftMax(tmp2Matr.addMatrix(mod.m_b2));  //完成softmax(relu(x * w1 + b1) * w2 + b2),r是公式计算结果向量
    return r;
}

std::vector<std::vector<double>> model_double::foward(matrix<double>& x,model<double>& mod){    
    matrix tmpMatr(x.multiplyMatrix(mod.m_w1));  //x*w1
    matrix tmp1Matr(mod.RELU(tmpMatr.addMatrix(mod.m_b1)));//完成relu(x * w1 + b1)操作
    matrix tmp2Matr(tmp1Matr.multiplyMatrix(mod.m_w2));  //relu(x * w1 + b1) * w2
    auto r=mod.SoftMax(tmp2Matr.addMatrix(mod.m_b2));  //完成softmax(relu(x * w1 + b1) * w2 + b2),r是公式计算结果向量
    return r;
}