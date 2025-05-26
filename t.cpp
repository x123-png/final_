#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
using namespace std;

int main(){
    vector<vector<int>> A(1000,vector<int>(1000,1));
    vector<vector<int>> B(1000,vector<int>(1000,1));
    vector<vector<int>> C(1000,vector<int>(1000,0));

    int line=1000;
    int row=1000;
    cout<<"开始计时"<<endl;
    auto start=chrono::high_resolution_clock::now();
    for(int l=0;l<line;l++){
        for(int r=0;r<row;r++){
            for(int i=0;i<row;i++){
                C[l][r]+=A[l][i]*B[i][r];
            }
        }
    }
    cout<<"结束计时"<<endl;
    // int threadNum=thread::hardware_concurrency();
    // int linesPerThread=line/threadNum;
    // vector<thread> threads;
    // auto start=chrono::high_resolution_clock::now();
    // for(int k=0;k<threadNum;k++){
    //     int startLine=k*linesPerThread;
    //     int endline=(k==threadNum-1)?line:startLine+linesPerThread;

    //     threads.emplace_back([&A,&B,&C,startLine,endline,row](){
    //         for(int l=startLine;l<endline;l++){
    //             for(int r=0;r<row;r++){
    //                 for(int i=0;i<row;i++){
    //                     C[l][r]+=A[l][i]*B[i][r];
    //                 }
    //             }
    //         }
    //     });
    // }

    // for(auto& t:threads){
    //     if(t.joinable()) t.join();
    // }
    cout<<"结束计时"<<endl;
    auto stop=chrono::high_resolution_clock::now();
    auto time=chrono::duration_cast<chrono::milliseconds>(stop-start);
    cout<<time.count()<<"ms/n"<<endl;
    // for(int l=0;l<(int)C.size();l++){
    //     for(int r=0;r<(int)C[0].size();r++){
    //         cout<<C[l][r]<<" ";
    //     }
    //     cout<<endl;
    // }

}