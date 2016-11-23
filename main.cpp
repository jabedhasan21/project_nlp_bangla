#include "Lib/Rules.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Rule a[100];

int main(){
    {
        ifstream cin("Dic/rules.dic");
        string x;
        int i = 0;
        while(cin >> x){
            a[i] = Rule(x);
            cout << a[i].headWord << endl;
            i++;
        }
    }
    
    string x;
    cin >> x ;
    cout << x << endl;
    
return 0;
}
