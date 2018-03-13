### Community detection measures

#### NMI(normalized mutual information)

NMI指标用来比较社区检测结果与真实结果的差异，取值区间在0~1之间，NMI值越大表示社区划分结果约接近真实结果。

使用方法： 

1. make （如编译不通过，修改makefile）
2. ./nmiMeasure input_file1 input_file2


#### modularity(模块度)

modularity用来比较网络中社区的划分情况，直观理解社区划分如果能让内部节点之间联系紧密，与社区外部节点稀疏，则社区划分效果越好。

使用方法：

1. make
2. ./modularity graph_file  community_file