//
//  modularity.hpp
//  modularity
//
//  Created by 胡家煊 on 2018/3/13.
//  Copyright © 2018年 iscas. All rights reserved.
//

#ifndef modularity_hpp
#define modularity_hpp

#include <stdio.h>
#include <vector>

#endif /* modularity_hpp */

class modularity{
    
private:
    
   
    
public:
    
    modularity();
    ~modularity();
    
    static void load_files(const char * inputfile1, const char * inputfile2);
    
    static int get_max_node_id();
    static std::vector<int> getDegree();
    static std::vector<int> getcommTableOfNodes();
    static std::vector<int> getCommInterEdgeNum();
    static std::vector<int> getCommInterNodesDegree();
    static double calcModularity();
};
