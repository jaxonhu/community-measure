
//  nmiMeasure.cpp
//  NmiMeasure
//
//  Created by 胡家煊 on 2018/3/12.
//  Copyright © 2018年 iscas. All rights reserved.
//

#include "nmiMeasure.hpp"
#include <fstream>
#include <math.h>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <stdio.h>

using namespace std;

nmiMeasure::nmiMeasure(void){
    
}

nmiMeasure:: nmiMeasure(const char * inputfile1, const char * inputfile2){
    this->inputfile1 = inputfile1;
    this->inputfile2 = inputfile2;
}

nmiMeasure::~nmiMeasure(void){

}

vector<vector<int> >   nmiMeasure::get_data_from_text(const char * inputfile){
    vector<vector<int> > res;
    ifstream in(inputfile, fstream::in);
    map<int, vector<int> > map_store;
    //读取文件
    string line;
    while(getline(in, line)){
        istringstream iss(line);
        if(line.find('#') != std::string::npos)
            continue;
        int node_id;
        int community_id;
        if(!(iss >> node_id >> community_id)){break;}
        map_store[community_id].push_back(node_id);
    }
    for(map<int, vector<int> >::iterator iter = map_store.begin() ; iter != map_store.end() ; iter ++){
        res.push_back(iter->second);
    }
    return res;
};

double nmiMeasure::log2(double x){
    return log(x)/log(2);
};

double nmiMeasure::h(double x){
    if (x > 0)
        return -1 * x * log2(x);
    else
        return 0;
};

long nmiMeasure::getNodesNum(vector<vector<int> > & X, vector<vector<int> > & Y){
    set<int> s;
    for(size_t i = 0 ; i < X.size() ; i++){
        for(size_t j = 0 ; j < X[i].size() ; j++){
            s.insert(X[i][j]);
        }
    }
    for(size_t i = 0 ; i < Y.size() ; i++){
        for(size_t j = 0 ; j < Y[i].size() ; j++){
            s.insert(Y[i][j]);
        }
    }
    return s.size();
};

vector<int> nmiMeasure::my_difference(std::vector<int> & Xi, std::vector<int> & Yj){
    
    sort(Xi.begin(), Xi.end());
    sort(Yj.begin(), Yj.end());
    vector<int> res;
    res.resize((max(Xi.size(),Yj.size())));
    auto iter = std::set_difference(Xi.begin(), Xi.end(), Yj.begin(), Yj.end(), res.begin());
    res.resize(iter - res.begin());
    return res;
}

vector<int> nmiMeasure::my_intersection(std::vector<int> & Xi, std::vector<int> & Yj){
    
    sort(Xi.begin(),Xi.end());
    sort(Yj.begin(), Yj.end());
    vector<int> res(max(Xi.size(), Yj.size()));
    auto iter = std::set_intersection(Xi.begin(), Xi.end(), Yj.begin(), Yj.end(), res.begin());
    res.resize(iter - res.begin());
    return res;
}

double  nmiMeasure::H(std::vector<int> X){
    
    double p1 = (double) X.size() / g_nodes_num;
    double p2 = 1 - p1;
    return h(p1) + h(p2);
};

double nmiMeasure::H_Xi_join_Yj(std::vector<int> & Xi, std::vector<int> & Yj){
    
    double p11 = (double) my_intersection(Xi, Yj).size() / g_nodes_num;
    double p10 = (double) my_difference(Xi, Yj).size() / g_nodes_num;
    double p01 = (double) my_difference(Yj, Xi).size() / g_nodes_num;
    double p00 = 1 - p11 - p10 - p01;
    
    if(h(p11) + h(p00) >= h(p10) + h(p01))
        return h(p11) + h(p10) + h(p01) + h(p00);
    else
        return H(Xi) + H(Yj);
};

double nmiMeasure::H_Xi_given_Yj(std::vector<int> & Xi, std::vector<int> & Yj){
    return H_Xi_join_Yj(Xi, Yj) - H(Yj);
};

double nmiMeasure::H_Xi_given_Y(std::vector<int> &Xi, std::vector<std::vector<int> > &Y){
    
    double res = H_Xi_given_Yj(Xi, Y[0]);
    for(size_t j = 1 ; j < Y.size() ; j++){
        res = min(res, H_Xi_given_Yj(Xi, Y[j]));
    }
    return res;
};

double nmiMeasure::H_X_given_Y(std::vector<std::vector<int> > &X, std::vector<std::vector<int> > &Y){
    double res = 0;
    for(size_t i = 0 ; i < X.size() ; i ++){
        res += H_Xi_given_Y(X[i], Y);
    }
    return res;
}

double nmiMeasure::H_Xi_given_Y_norm(std::vector<int> &Xi, std::vector<std::vector<int> > &Y){
    return (double) H_Xi_given_Y(Xi, Y) / H(Xi);
}

double nmiMeasure::H_X_given_Y_norm(std::vector<std::vector<int> > &X, std::vector<std::vector<int> > &Y){
    double res = 0;
    for(size_t i = 0 ; i < X.size() ; i++){
        res += H_Xi_given_Y_norm(X[i], Y);
    }
    return res / X.size();
};

double nmiMeasure::nmi(std::vector<std::vector<int> > &X, std::vector<std::vector<int> > &Y){
    if(X.size() == 0 || Y.size() == 0)
        return 0;
    else{
        g_nodes_num = getNodesNum(X, Y);
        return 1 - 0.5 * (H_X_given_Y_norm(X, Y) + H_X_given_Y_norm(Y, X));
    }
};






