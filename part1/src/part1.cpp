#include "part1.h"
#include <iostream>
#include <cmath>
//共有20个线程
//本程序中l是行，r是列
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

//矩阵的乘法A*B
template<class T>
std::vector<std::vector<T>> matrix<T>::multiplyMatrix(std::vector<std::vector<T>> const matr){  //乘以的矩阵
    std::vector<std::vector<T>> result(line,std::vector<T>(matr[0].size(),0));  //初始化结果矩阵
    int lineA=line;
    int rowB=matr[0].size();
    int threadNum=std::thread::hardware_concurrency();
    std::vector<std::thread> threads; //每次运行的线程
    int linesPerThread=lineA/threadNum;//每次处理的行数

    for(int k=0;k<threadNum;k++){
        int startLine=k*linesPerThread;
        int endLine=(k==threadNum-1)?lineA:(startLine+linesPerThread);

        threads.emplace_back([&result,startLine,endLine,rowB,this,&matr](){
            for(int i=0;i<this->row;i++){  
                for(int l=startLine;l<endLine;l++){ //结果的行 
                    for(int r=0;r<rowB;r++){
                        result[l][r]+=this->localMatrix[l][i]*matr[i][r];
                    }
                }        
            }
        });
    }
    
    for(auto& t:threads){
        if(t.joinable()){
            t.join();
        }
    }
    // for(int l=0;l<line;l++){  
    //     for(int r=0;r<matr[0].size();r++){ //结果的行 
    //         for(int i=0;i<row;i++){
    //             result[l][r]+=localMatrix[l][i]*matr[i][r];
    //         }
    //     }        
    // }
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
    std::vector<std::vector<T>> soft(1,std::vector<T>(10,0));
    float deno=0;  //分母
    for(int i=0;i<v[0].size();i++){
        deno+=std::pow(e,v[0][i]);
    }
    for(int i=0;i<v[0].size();i++){
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