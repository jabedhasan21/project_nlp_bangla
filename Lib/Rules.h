#ifndef RULES_H
#define RULES_H
#include <string>
#include <vector>
using namespace std;

struct Rule{
    string word,headWord, uniWord;
    vector<string> restrictions;
    vector<string> attributes;
    
    Rule();
    Rule(string _rule);
    void Parse(string s);
};
#endif
