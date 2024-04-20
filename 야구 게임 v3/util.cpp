#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

string randnum(){
    srand((unsigned int)time(NULL));
    int randnum = 0;
    string randstring;
    
    while(true){
        randnum = (rand() % 999) + 11;
        int num100 = randnum / 100;
        int num10 = (randnum % 100) / 10;
        int num1 = (randnum % 100) % 10;

        if((num100 != num10) && (num100 != num1) && (num10 != num1)){
            break;
        }
    }
    if(randnum < 100){
        randstring = to_string(randnum);
        randstring.insert(0, "0");
    }
    else
        randstring = to_string(randnum);
    
    return randstring;
}