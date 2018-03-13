//
//  modularity.cpp
//  modularity
//
//  Created by jaxonhu on 2018/3/13.
//  Copyright © 2018年 iscas. All rights reserved.
//

#include "modularity.hpp"

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;


vector<pair<int,int> > graph;
vector<vector<int> > communities;

modularity::modularity(void){
    
    
};

modularity::~modularity(void){
    
};

void modularity::load_files(const char * inputfile1, const char * inputfile2){
    
    map<int, vector<int> > map_community;
    
    ifstream in(inputfile1, fstream::in);
    string line;
    while(getline(in, line)){
        istringstream iss(line);
        if(line.find('#') != std::string::npos)
            continue;
        int src_id, dst_id;
        if(!(iss >> src_id >> dst_id)){break;}
        pair<int, int> edge(src_id, dst_id);
        graph.push_back(edge);
    }
    in.close();
    
    ifstream in2(inputfile2, fstream::in);
    while(getline(in2, line)){
        istringstream iss(line);
        if(line.find('#') != std::string::npos)
            continue;
        int community_id, node_id;
        if(!(iss >> node_id >> community_id)){break;}
        map_community[community_id].push_back(node_id);
    }
    
    for(map<int, vector<int> >::iterator iter = map_community.begin() ; iter != map_community.end() ; iter ++){
        communities.push_back(iter->second);
    }
}

//最大节点编号
int modularity::get_max_node_id()
{
    int res = 0;
    for (size_t i = 0; i < graph.size(); ++i)
    {
        res = max(res, graph[i].first);
        res = max(res, graph[i].second);
    }
    return res;
}
//返回每个结点的度
vector<int> modularity::getDegree()
{
    vector<int> d(get_max_node_id() + 1, 0);
    for (size_t i = 0; i < graph.size(); ++i)
    {
        ++d[graph[i].first];
        ++d[graph[i].second];
    }
    return d;
}

//返回一个记录每个结点所属社团号的向量
vector<int> modularity::getcommTableOfNodes()
{
    vector<int> res;
    res.resize(get_max_node_id()+1);
    for (size_t i = 0; i < communities.size(); ++i)
    {
        const vector<int> & nodes = communities[i];
        for (size_t j = 0; j < nodes.size(); ++j)
        {
            res[nodes[j]] = i;
        }
    }
    return res;
}

//社团内部的边数
vector<int> modularity::getCommInterEdgeNum()
{
    vector<int> v(communities.size(), 0);
    for (size_t i = 0; i < graph.size(); ++i)
    {
        int x = graph[i].first;
        int y = graph[i].second;
        
        vector<int> cid = getcommTableOfNodes();
        
        if (cid[x] == cid[y])
        {
            ++v[cid[x]];
        }
    }
    return v;
}

//社团内部结点的度数之和
vector<int> modularity::getCommInterNodesDegree()
{
    vector<int> degree = getDegree();
    vector<int> v(communities.size(), 0);
    for (size_t i = 0; i < communities.size(); ++i)
    {
        for (size_t j = 0; j < communities[i].size(); ++j)
            v[i] += degree[communities[i][j]];
    }
    return v;
}

double modularity::calcModularity()
{
    //社团个数 ==3
    int nc = communities.size();
    //社团内部的边数 ==[5, 7, 8]
    vector<int> comm_inter_edge_num = getCommInterEdgeNum();
    //社团内部点的度数之和 ==[11, 17, 18]
    vector<int> comm_inter_nodes_degree = getCommInterNodesDegree();
    //总边数 ==23
    double m = graph.size();
    double Q = 0;
    for (int i = 0; i < nc; ++i)
    {
        Q += (comm_inter_edge_num[i] / m) - (comm_inter_nodes_degree[i] / (2 * m)) * (comm_inter_nodes_degree[i] / (2 * m));
    }
    return Q;
}

