#include <string>
#include <vector>
#include "Rules.h"
#include <iostream>

using namespace std;

Rule::Rule(){
    headWord = uniWord = "";
    restrictions.clear();
    attributes.clear();
}

void Rule::Parse(string s){
    int i = 1;
    
    while(i < s.length() && s[i] != ']'){
        headWord += s[i];
        i++;
    }
    
    while(i < s.length() && s[i] != '\"')
        i++;
    i++;
    
    if (s[i] != '\"'){
        while(i < s.length() && s[i] != '('){
            uniWord += s[i];
            i++;
        }
        
        while(i < s.length() && s[i] != ')'){
            string tmp;
            i++;
            
            while(i < s.length() && (s[i] != ',' && s[i] != ')')){
                tmp += s[i];
                i++;
            }
            
            restrictions.push_back(tmp);
        }
    }
    
    while(i < s.length() && s[i] != '(')    i++;
    
    while(i < s.length() && s[i] != ')'){
        i++;
        string tmp;
        
        while (i < s.length() && (s[i] != ',' && s[i] != ')')){
            tmp += s[i];
            i++;
        }
        
        attributes.push_back(tmp);
    }
}

Rule::Rule(string _rule){
    Parse(_rule);
}
