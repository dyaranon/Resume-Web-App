#ifndef PALINDROME_HPP
#define PALINDROME_HPP

#include <unordered_map>
#include <vector>
#include <algorithm>
#include <regex>
#include "crow_all.h"

using namespace std;

 nlohmann::json getPalindromes(string data){
    nlohmann::json x;
    unordered_map<string, bool> hashmap;
    string word = "";
    std::string::size_type i = data.find("%20");
    while (i != std::string::npos){
        data.erase(i, 3);
        data.insert(i, " ");
        i = data.find("%20", i);
    }
    for(int i = 0; i < data.size(); i++){
        if(data[i] == ' '){
            hashmap.insert({word, true});
            word = "";
        }
        else{
            word += data[i];
        }
    }
    string temp;
    vector<string> words;
    int numValid = 0;
    for(auto& i: hashmap){
        temp = i.first;
        reverse(temp.begin(), temp.end());
        auto got = hashmap.find(temp);
        if(got != hashmap.end()){
            words.push_back(i.first);
            numValid++;
        }
    }
    x["words"] = words;
    x["numValid"] = numValid;
    return x;
}

#endif
