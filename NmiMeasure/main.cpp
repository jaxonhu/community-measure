//
//  main.cpp
//  NmiMeasure
//
//  Created by 胡家煊 on 2018/3/12.
//  Copyright © 2018年 iscas. All rights reserved.
//

#include <iostream>
#include "nmiMeasure.hpp"

using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    
    const char * inputfile1 = argv[1];
    const char * inputfile2 = argv[2];
    
    cout<<"Usage: input two arguments, input file and real community file." << endl;
    
    nmiMeasure nmi_measure;
    
    std::vector<std::vector<int> >  X = nmiMeasure::get_data_from_text(inputfile1);
    std::vector<std::vector<int> >  Y = nmiMeasure::get_data_from_text(inputfile2);
    double nmi = nmi_measure.nmi(X, Y);
    cout << "Normalized Mutual Information: " << nmi <<endl;
    return 0;
}
