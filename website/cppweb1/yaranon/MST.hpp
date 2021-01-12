#ifndef MST_HPP
#define MST_HPP

#include <map>
#include <list>
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <string>
#include "json.h"

using namespace std;

struct Graph {
    list<string> vertices;
    map<pair<string,string>,int> edges;
    std::list<pair<int, int>>* adjacent;
    std::priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

    void PrintOut() {
        list<string>::iterator it;
        map<pair<string,string>,int>::iterator eit;

        for(it=vertices.begin(); it!=vertices.end(); it++) {
            cout << *it << endl;
        }

        for(eit = edges.begin(); eit != edges.end(); eit++) {
            cout << (*eit).first.first << " " << (*eit).first.second << " " << (*eit).second << endl;
        }
    }

    void AddEdge(int u, int v, int w){
        pair<int, int> p1(v, w);
        pair<int, int> p2(u, w);
        adjacent[u].push_back(p1);
        adjacent[v].push_back(p2);
    }

    bool FindVertex(string vert1) {
        auto it = find(this->vertices.begin(),  this->vertices.end(), vert1);
        if(it != this->vertices.end()){
            return 1;
        }
        return 0;
    }

    int FindEdgeCost(string vert1, string vert2) {
        map<pair<string,string>,int> copy = this->edges;
        if(FindVertex(vert1) && FindVertex(vert2)){
            pair<string,string> names(vert1, vert2);
            if(copy[names] != 0){
                return copy[names];
            }
        }
        return -1;
    }

    //pg595 textbook Algorithms 3rd edition
    int IsReachable(string vert1, string vert2) {
        map<string, int> distance;
        queue<string> Q;
        list<string> copy = this->vertices;
        string u, adjacent;
        for(int i = 0; i < this->vertices.size(); i++){
            distance.insert({copy.front(), 1000000});
            copy.pop_front();
        }
        distance[vert1] = 0;
        Q.push(vert1); //enqueue source vertex
         while(Q.size() > 0){
           u = Q.front();
           Q.pop();
           for(auto it = edges.begin(); it != edges.end()   ; it++){
               if(((*it).first).first == u){
                   adjacent = ((*it).first).second;
                   if(distance[adjacent] == 1000000) { //   Hasn't been processed yet
                       distance[adjacent] = distance[u] +   1;
                       Q.push(adjacent); //dequeue
                   }
               }
           }
       }
       if(distance[vert2] != 1000000){ //If there is a  connection between vert1 and vert2
           return distance[vert2];
       }
       return -1;
    }

    //pseudo-code of Prim’s algorithm given in Lab16 manual
    vector<int> minSpanTree(int V){
        int u, v, w, r = 0;
        vector<int> key;
        vector<int> p;
        vector<bool> valid;
        for(int i = 0; i < V; i++){
            key.push_back(1000000);
            p.push_back(-1000000);
            valid.push_back(0);
        }
        pair<int, int> source(0, r);
        minHeap.push(source);
        key[r] = 0;
        while (minHeap.size()!= 0){
        	u = minHeap.top().second;
        	minHeap.pop();
    	    valid[u] = 1;
        	for (auto it = adjacent[u].begin(); it != adjacent[u].end(); ++it){
            	v = (*it).first;
            	w = (*it).second;
            	if (valid[v] == 0 && key[v] > w){
                    p[v] = u;
                	key[v] = w;
                    pair<int, int> temp(key[v], v);
                	minHeap.push(temp);
            	}
        	}
        }
        return p;
    }

    nlohmann::json MST(int V, int E, std::string data){
        nlohmann::json x;
        std::string num = "";
        vector<int> u, v, w;
        adjacent = new list<pair<int, int>> [V];
        vector<int> nums;
        for(int i = 0; i < data.size(); i++){
            if(data[i] != ','){
                num += data[i];
            }
            else{
                nums.push_back(stoi(num));
                num = "";
            }
        }
        for(int i = 0; i < nums.size(); i+=3){
            AddEdge(nums[i], nums[i+1], nums[i+2]);
        }
    	vector<int> p = minSpanTree(V);
        x["ans"] = p;
        return x;
    }
};

#endif