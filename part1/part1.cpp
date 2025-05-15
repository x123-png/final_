#include "part1.h"
#include <iostream>
#include <cmath>

std::vector<std::vector<float>> matrix::getMatrix(){
    return localMatrix;
}

std::vector<std::vector<float>> matrix::addMatrix(std::vector<std::vector<float>> matr){
    for(int l=0;l<line;l++){
        for(int r=0;r<row;r++){
            localMatrix[l][r]+=matr[l][r];
        }
    }
    return localMatrix;
}

int matrix::getLine(){
    return line;
}

int matrix::getRow(){
    return row;
}

std::vector<std::vector<float>> matrix::multiplyMatrix(std::vector<std::vector<float>> const matr){
    std::vector<std::vector<float>> result;
    for(int l=0;l<line;l++){  //结果的行
        for(int r=0;r<matr[0].size();r++){  
            for(int i=0;i<line;i++){
                result[l][r]=localMatrix[l][i]*matr[i][r];
            }
        }        
    }
    return result;
}

std::vector<std::vector<float>> model::RELU(matrix matr){
    std::vector<std::vector<float>> m=matr.getMatrix();
    for(int l=0;l<matr.getLine();l++){
        for(int r=0;r<matr.getRow();r++){
            if(m[l][r]<0) m[l][r]=0;
        }
    }
    return m;
}

std::vector<std::vector<float>> model::SoftMax(std::vector<std::vector<float>> v){
    float e=2.718;
    std::vector<std::vector<float>> soft;
    float deno;
    for(int i=0;i<v.size();i++){
        deno+=std::pow(e,v[0][i]);
    }
    for(int i=0;i<v.size();i++){
        soft[0][i]=std::pow(e,v[0][i])/deno;
    }
    return soft;
}