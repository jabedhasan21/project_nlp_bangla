#include "Lib/Rules.h"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>

#define PB push_back

using namespace std;

Rule a[100];
map<string, vector<string> > words;
string subject[2], object[2],verb[2];
vector<Rule> sR[2], oR[2], vR[2];

void CheckingKBIV(){
    for (int i=0;i<vR[1].size();i++){
        bool flg = 0;
        flg = 0;
        for (int j=0;j<vR[1][i].attributes.size();j++){
            if (vR[1][i].attributes[j]== "KBIV"){
                flg = 1;
            }
        }
        
        if (!flg){
            vR[1].erase(vR[1].begin()+i);
            i--;
        }
    }
}

void CheckingOBIV(){
    for (int i=0;i<oR[1].size();i++){
        for (int j=0;j<oR[1][i].attributes.size();j++){
            if (oR[1][i].attributes[j]== "KBIV"){
                oR[1].erase(oR[1].begin()+i);
                i--;
                break;
            }
        }
    }
}

pair< bool, pair< string,string> > CheckingPersion(){
    string _1p2p3p;
    
    for (int i=0;i<sR[0].size();i++){
        for (int j=0;j<sR[0][i].attributes.size();j++){
            if (sR[0][i].attributes[j] == "1P")
                _1p2p3p = "1P";
            
            if (sR[0][i].attributes[j] == "2P")
                _1p2p3p = "2P";
                
            if (sR[0][i].attributes[j] == "3P")
                _1p2p3p = "3P";
        }
    }
    
    bool flg = 0;
    
    string _vp;
    
    for (int i=0;i<vR[1].size();i++){
        for (int j=0;j<vR[1][i].attributes.size();j++){
            if (vR[1][i].attributes[j] == _1p2p3p)
                flg = 1;
                
            if (vR[1][i].attributes[j] == "1P")
                _vp = "1P";
            
            if (vR[1][i].attributes[j] == "2P")
                _vp = "2P";
                
            if (vR[1][i].attributes[j] == "3P")
                _vp = "3P";
        }
    }
    
    return make_pair( flg, make_pair( _1p2p3p, _vp ) );
}

int main(){
    int len = 0;
    {
        ifstream cin("Dic/rules.dic");
        string x;
        
        while(cin >> x){
            a[len] = Rule(x);
            len++;
        }
    }
    
    {
        ifstream cin ("Dic/biv.dic");
        
        string x;
        
        while(cin >> x){
            pair< string, vector<string> > y;
            
            y = Rule().detachWord(x);
            
            words[y.first] = y.second;
        }
    }
    
    string x,y;
    
    getline(cin,x);
    
    vector< string > wd;
    stringstream ss;
    ss << x;
    
    while(ss >> y){
        if (words.find(y) == words.end()){
            wd.push_back(y);
            wd.push_back("");
        }
            
        else{
            wd.push_back(words[y][0]);
            wd.push_back(words[y][1]);
        }
    }
    
    subject[0] = wd[0];     
    subject[1] = wd[1];     
    
    object[0] = wd[2];      
    object[1] = wd[3];      
    
    verb[0] = wd[4];        
    verb[1] = wd[5];        
    
    for (int i=0;i<len;i++){
        if (a[i].headWord == subject[0])
            sR[0].PB(a[i]);
            
        if (a[i].headWord == subject[1])
            sR[1].PB(a[i]);
            
        if (a[i].headWord == object[0])
            oR[0].PB(a[i]);
            
        if (a[i].headWord == object[1])
            oR[1].PB(a[i]);
            
        if (a[i].headWord == verb[0])
            vR[0].PB(a[i]);
            
        if (a[i].headWord == verb[1])
            vR[1].PB(a[i]);
    }
    
    CheckingKBIV();
    CheckingOBIV();
    pair<bool, pair< string,string > > flg = CheckingPersion();
    
    if (!flg.first){
        printf("Error!!!\n");
        printf("Here verb is of ");
        
        if (flg.second.second == "1P")    printf ("1st person");
        if (flg.second.second == "2P")    printf ("2nd person");
        if (flg.second.second == "3P")    printf ("3rd person");
        
        printf (" but subject is ");
        
        if (flg.second.first == "1P")    printf ("1st person");
        if (flg.second.first == "2P")    printf ("2nd person");
        if (flg.second.first == "3P")    printf ("3rd person");
        puts("");
    }
    
    else{
        for (int i=0;i<sR[0].size();i++)    sR[0][i].Print();
        for (int i=0;i<sR[1].size();i++)    sR[1][i].Print();
        for (int i=0;i<oR[0].size();i++)    oR[0][i].Print();
        for (int i=0;i<oR[1].size();i++)    oR[1][i].Print();
        
        for (int i=0;i<vR[0].size();i++)    vR[0][i].Print();
        for (int i=0;i<vR[1].size();i++)    vR[1][i].Print();
    }
return 0;
}
