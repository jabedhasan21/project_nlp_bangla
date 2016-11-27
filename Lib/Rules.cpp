#include <string>
#include <vector>
#include "Rules.h"
#include <iostream>
#include <stdio.h>

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

pair<string, vector<string> > Rule::detachWord(string _s){
    string wd;
    int i;
    
    for (i=1;_s[i] != '}';i++)
        wd += _s[i];
        
    i++;i++;i++;
    
    string part1,part2;
    
    for (;_s[i] != ',';i++)
        part1 += _s[i];
        
    i++;
    
    for (;_s[i] != ']';i++)
        part2 += _s[i];
        
    //cout << wd << " " << part1 << " " << part2 << endl;
    
    vector<string> v;
    v.push_back(part1);
    v.push_back(part2);
    
    return make_pair( wd, v );
}

void Rule::Print(){
    printf ("[%s]{}\"%s(",headWord.c_str(),uniWord.c_str());
    
    for (int i=0;i<restrictions.size();i++){
        printf("%s",restrictions[i].c_str());
        
        if (i != restrictions.size() -1)
            printf(",");
    }
    
    printf(")\"(");
    
    for (int i=0;i<attributes.size();i++){
        printf("%s",attributes[i].c_str());
        
        if (attributes.size() - 1 != i)
            printf (",");
    }
    
    printf (")\n");
}
