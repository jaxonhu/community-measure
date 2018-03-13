//
//  nmiMeasure.hpp
//  NmiMeasure
//
//  Created by jaxonhu on 2018/3/12.
//  Copyright © 2018年 iscas. All rights reserved.
//

#ifndef nmiMeasure_hpp
#define nmiMeasure_hpp

#include <stdio.h>
#include <vector>
#include <iostream>

#endif /* nmiMeasure_hpp */


class nmiMeasure{
    
private:
    
    const char * inputfile1;
    const char * inputfile2;
    
    long g_nodes_num;

public:
    nmiMeasure(void);
    ~nmiMeasure(void);
    
    nmiMeasure(const char * inputfile1, const char * inputfile2);
    
    static std::vector<std::vector<int> > get_data_from_text(const char * inputfile);
    
    
    //NMI的计算输入是两种社区划分的结果。exp. X[0] 保存属于X划分方法中属于第一个社区的顶点
    double NMI(std::vector<std::vector<int> > & X, std::vector<std::vector<int> > & Y);
    //计算X和Y的标准条件信息熵
    double H_X_given_Y_norm(std::vector<std::vector<int> > & X, std::vector<std::vector<int> > & Y);
    //计算Xi和Y的标准条件信息熵
    double H_Xi_given_Y_norm(std::vector<int> & Xi, std::vector<std::vector<int> > & Y);
    //计算Xi和Y的条件信息熵
    double H_Xi_given_Y(std::vector<int> & X, std::vector<std::vector<int> > & Y);
    //计算Xi和Yj的条件信息熵
    double H_Xi_given_Yj(std::vector<int> & Xi, std::vector<int> & Yj);
    //计算Xi和Yj的联合信息熵
    double H_Xi_join_Yj(std::vector<int> & Xi, std::vector<int> & Yj);
    //计算X和Y的条件信息熵
    double H_X_given_Y(std::vector<std::vector<int> > & X, std::vector<std::vector<int> > & Y);
    //计算NMI
    double nmi(std::vector<std::vector<int> > & X, std::vector<std::vector<int> > & Y);
    
    //计算Xi的信息熵
    double H(std::vector<int> X);
    
    
    //返回集合差集
     std::vector<int> my_difference(std::vector<int> & Xi, std::vector<int> & Yj);
    //返回集合交集
     std::vector<int> my_intersection(std::vector<int> & Xi, std::vector<int> & Yj);
    
    double log2(double x);
    double h(double x);
    long getNodesNum(std::vector<std::vector<int> > & X, std::vector<std::vector<int> > & Y);
    
    
};
