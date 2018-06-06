#include<bits/stdc++.h>

using namespace std;

int main(){

    for(int i=10; i<=30; i++){
        for(int j=i%10; j<10; j+=2){
            switch(j){

            case 0:
            case 2:
            case 4:
            case 6:
            case 8:
                cout<<"Even number."<<endl;
                break;
            default:
                cout<<"Odd number."<<endl;

            }
        }
    }
    return 0;
}
