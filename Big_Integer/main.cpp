#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main(){
    string firNum;
    string secNum;
    string sum;
    string sub;
    int carry = 0;
    cin >> firNum;
    cin >> secNum;
    if(firNum.length() >= secNum.length()){
        for(int i = 0; i < firNum.length() - secNum.length(); i++){
            secNum.insert(i, "0");
        }
        int n1, n2;
        for(int i = -1; i >= -firNum.length(); i--){
            n1 = firNum[i] - '0';
            n2 = secNum[i] - '0';
            if((n1 + n2) % 10 + carry == 10){
                carry = 1;
                sum.push_back(0);
            }

            else{
                sum.push_back((char)((n1 + n2) % 10 + carry));
                carry = (n1 + n2) / 10;
            }
        }

        if(carry != 0){
            sum.push_back((char)carry);
        }
    }
    
    for(int i = sum.length() - 1; i >= 0; i--){
        cout << sum[i] << endl;
    }
}