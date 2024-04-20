#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

string randnum();

void game1(){
    srand((unsigned int)time(NULL));
    int n = 5;
    string answer = randnum();
    string guess;

    do{
        int strikes = 0;
        int balls = 0;
        cout << n << "chances left" << endl;
        cout << "Enter a guess: " << endl;
        cin >> guess;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(answer[i] == guess[j]){
                    if(i == j) strikes++;
                    else if(i != j) balls++;
                }
            }
        }
        cout << "Strikes: " << strikes << " Balls: " << balls << endl;
        n--;
        if(n == 0){
            break;
        }
    }while(answer != guess);

    if(n == 0){
        cout << "You Lose!" << endl;
    }

    else{
        cout << "You Win!" << endl;
    }
}