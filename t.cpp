#include <iostream>
#include <thread>
#include <vector>
using namespace std;

int main(){
    vector<vector<int>> A(10,vector<int>(10,1));
    vector<vector<int>> B(10,vector<int>(10,1));
    vector<vector<int>> C(10,vector<int>(10,0));

    int line=10;
    int row=10;
    int threadNum=thread::hardware_concurrency();
    int linesPerThread=line/threadNum;
    vector<thread> threads;
    for(int k=0;k<threadNum;k++){
        int startLine=k*linesPerThread;
        int endline=(k==threadNum-1)?line:startLine+linesPerThread;

        threads.emplace_back([&A,&B,&C,startLine,endline,row](){
            for(int l=startLine;l<endline;l++){
                for(int r=0;r<row;r++){
                    for(int i=0;i<row;i++){
                        C[l][r]+=A[l][i]*B[i][r];
                    }
                }
            }
        });
    }

    for(auto& t:threads){
        if(t.joinable()) t.join();
    }

    for(int l=0;l<(int)C.size();l++){
        for(int r=0;r<C[0].size();r++){
            cout<<C[l][r]<<" ";
        }
        cout<<endl;
    }

}