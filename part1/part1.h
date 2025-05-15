#pragma once
#include <vector>

//矩阵类,完成确定矩阵的大小，矩阵的乘法和加法
class matrix{
    private:
        std::vector<std::vector<float>> localMatrix; //矩阵
        int line; //行数大小
        int row;   //列大小 
    public:
    int getLine();
    int getRow();
    matrix(std::vector<std::vector<float>>inputMatrix):localMatrix(inputMatrix),line(localMatrix.size()),row(localMatrix[0].size()){}; //构造矩阵对象
    std::vector<std::vector<float>> getMatrix();  //返回矩阵
    std::vector<std::vector<float>> addMatrix(std::vector<std::vector<float>>);//矩阵的加法
    std::vector<std::vector<float>> multiplyMatrix(std::vector<std::vector<float>> const);//矩阵的乘法
};

//model类
class model{
    public:
        std::vector<std::vector<float>> m_w1;
        std::vector<std::vector<float>> m_b1;
        std::vector<std::vector<float>> m_w2;
        std::vector<std::vector<float>> m_b2;
    model(std::vector<std::vector<float>>w1,std::vector<std::vector<float>>b1
        ,std::vector<std::vector<float>>w2,std::vector<std::vector<float>>b2):m_w1(w1),m_b1(b1),m_w2(w2),m_b2(b2){};
    std::vector<std::vector<float>> RELU(matrix);  //RELU函数，将矩阵中小于零的数变为0 
    std::vector<std::vector<float>> SoftMax(std::vector<std::vector<float>>); //SoftMax函数
};