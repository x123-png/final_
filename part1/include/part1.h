#pragma once
#include <vector>
#include <thread>

//矩阵类,完成确定矩阵的大小，矩阵的乘法和加法
template<class T>
class matrix{
    private:
        std::vector<std::vector<T>> localMatrix; //矩阵
        int line; //行数大小
        int row;   //列大小
    public:
    int getLine();
    int getRow();
    matrix(std::vector<std::vector<T>>inputMatrix):localMatrix(inputMatrix),line(localMatrix.size()),row(localMatrix[0].size()){}; //构造矩阵对象
    std::vector<std::vector<T>> getMatrix();  //返回矩阵
    std::vector<std::vector<T>> addMatrix(std::vector<std::vector<T>>);//矩阵的加法
    std::vector<std::vector<T>> multiplyMatrix(std::vector<std::vector<T>> const);//矩阵的乘法
};

//model类
template<class T>
class model{
    public:
        std::vector<std::vector<T>> m_w1;
        std::vector<std::vector<T>> m_b1;
        std::vector<std::vector<T>> m_w2;
        std::vector<std::vector<T>> m_b2;
        model(std::vector<std::vector<T>>w1,std::vector<std::vector<T>>b1
        ,std::vector<std::vector<T>>w2,std::vector<std::vector<T>>b2):m_w1(w1),m_b1(b1),m_w2(w2),m_b2(b2){};  //构造函数没问题
        std::vector<std::vector<T>> RELU(std::vector<std::vector<T>>);  //RELU函数，将矩阵中小于零的数变为0 
        std::vector<std::vector<T>> SoftMax(std::vector<std::vector<T>>); //SoftMax函数
        virtual std::vector<std::vector<T>> foward(matrix<T>&,model<T>&)=0;//forward封装计算过程
};

class model_float:public model<float>{
    public:
        model_float(std::vector<std::vector<float>>w1,std::vector<std::vector<float>>b1
            ,std::vector<std::vector<float>>w2,std::vector<std::vector<float>>b2):model<float>(w1,b1,w2,b2){};    
        std::vector<std::vector<float>> foward(matrix<float>&,model<float>&) override;
};

class model_double:public model<double>{
    public:
        model_double(std::vector<std::vector<double>>w1,std::vector<std::vector<double>>b1
            ,std::vector<std::vector<double>>w2,std::vector<std::vector<double>>b2):model<double>(w1,b1,w2,b2){};
        std::vector<std::vector<double>> foward(matrix<double>&,model<double>&) override;
};