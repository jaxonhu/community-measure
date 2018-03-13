//
//  main.cpp
//  modularity
//
//  Created by jaxonhu on 2018/3/13.
//  Copyright © 2018年 iscas. All rights reserved.
//

#include <iostream>
#include "modularity.hpp"

int main(int argc, const char * argv[]) {
    
    // insert code here...
    std::cout << "Using manual:!\n";
    std::cout << "two arguments, first is graph edge dataset, second is community detection results:!\n";
    const char * inputfile1 = argv[1];
    const char * inputfile2 = argv[2];
    modularity m;
    m.load_files(inputfile1, inputfile2);
    double Q = m.calcModularity();
    std::cout<<"Modularity: " << Q<<std::endl;
 
}
